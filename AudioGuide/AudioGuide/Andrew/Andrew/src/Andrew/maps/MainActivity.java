package Andrew.maps;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Locale;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore.Audio.Media;
import android.speech.tts.TextToSpeech;
import android.speech.tts.TextToSpeech.OnInitListener;
import android.text.InputFilter.LengthFilter;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.MapFragment;
import com.google.android.gms.maps.model.BitmapDescriptorFactory;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.Marker;
import com.google.android.gms.maps.model.MarkerOptions;

import Andrew.maps.ContextoDados.PontosCursor;

public class MainActivity extends Activity implements OnInitListener{

	Button button;
	Button button2;
	static AlertDialog menu = null;
	int fechar = 0;
	
	private float dist1n = 5.0f;
	private float dist2n = 15.0f;
	private static float dist3n = 30.0f;
	
	private String dist1t = "cinco";
	private String dist2t = "quinze";
	private String dist3t = "trinta";
	
	private static final int INTENT_TEXT_SPEECH_CODE = 9;
	private TextToSpeech textSpeech = null;
	private String textoQueSeraFalado = "";
    
	// Google Map
    public static GoogleMap googleMap;
    public static Context context;
    private static ArrayList<Marker> marks = new ArrayList<Marker>();
    private static ArrayList<Float> distmarks = new ArrayList<Float>();
    // GPSTracker class
    GPSTracker gps;
    
    
    
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
    	if (keyCode == KeyEvent.KEYCODE_MENU) {
    		showPopUp();
            return true;
        }
    	
    	return super.onKeyUp(keyCode, event);
    }
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        addListenerOnButton();
        
        context = this;
        
		//findViewById(R.id.sign_in_button).setOnClickListener(this);
        
      //-18.734274, -47.503240
        try {
            // Loading map
            initilizeMap();
            
            //latitude and longitude
            double latitude = -18.7306633;
            double longitude = -47.493034;
            
            // create class object
            gps = new GPSTracker(MainActivity.this);
            
         	// check if GPS enabled     
            if(gps.canGetLocation()){
                 
                latitude = gps.getLatitude();
                longitude = gps.getLongitude();
                 
                // \n is for new line
                Toast.makeText(getApplicationContext(), "Your Location is - \nLat: " + latitude + "\nLong: " + longitude, Toast.LENGTH_LONG).show();    
            }else{
                // can't get location
                // GPS or Network is not enabled
                // Ask user to enable GPS/network in settings
                gps.showSettingsAlert();
            }
            
            googleMap.setMapType(GoogleMap.MAP_TYPE_NORMAL);
            //googleMap.setMapType(GoogleMap.MAP_TYPE_HYBRID);
            //googleMap.setMapType(GoogleMap.MAP_TYPE_SATELLITE);
            //googleMap.setMapType(GoogleMap.MAP_TYPE_TERRAIN);
            //googleMap.setMapType(GoogleMap.MAP_TYPE_NONE);
             
            
            // create marker
            //MarkerOptions marker = new MarkerOptions();
            //marker.position(new LatLng(latitude, longitude)).title("Origin");
            //marker.position(LOWER_MANHATTAN);
            //marker.position(BROOKLYN_BRIDGE);
            //marker.position(WALL_STREET);
            //MarkerOptions marker2 = new MarkerOptions().position(new LatLng(latitude2, longitude2)).title("Destin");
            
            // GREEN color icon
            //marker.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_GREEN));
            //marker2.icon(BitmapDescriptorFactory.defaultMarker(BitmapDescriptorFactory.HUE_RED));

            // adding marker
            //googleMap.addMarker(marker);
            //googleMap.addMarker(marker2);
            
            //CameraPosition cameraPosition = new CameraPosition.Builder().target(
                    //new LatLng(latitude, longitude)).zoom(zoom).build();
            
            //googleMap.animateCamera(CameraUpdateFactory.newCameraPosition(cameraPosition));
            
            //LatLng startPoint = new LatLng(latitude, longitude);
            //LatLng endPoint = new LatLng(latitude2, longitude2);
            
            
            
            //googleMap.moveCamera(CameraUpdateFactory.newLatLngZoom(endPoint, 15));
            googleMap.setMyLocationEnabled(true);
         // Getting LocationManager object from System Service LOCATION_SERVICE

            googleMap.setOnMyLocationChangeListener(myLocationChangeListener);
            //googleMap.animateCamera(CameraUpdateFactory.zoomTo(10),2000,null);
            
            // Getting URL to the Google Directions API
            //String url = getMapsApiDirectionsUrl(ROTAS.RotaPlus());

            //DownloadTask downloadTask = new DownloadTask();

            // Start downloading json data from Google Directions API
            //downloadTask.execute(url);
            
            googleMap.moveCamera(CameraUpdateFactory.newLatLngZoom(new LatLng(latitude, longitude),
    				16));
            
            addMarkers();
 
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    //public static void addMarkers() {
		/*if (googleMap != null) {
			for(LatLng l : ROTAS.RotaPlus()) {
				googleMap.addMarker(new MarkerOptions().position(l)
						.title("Ponto "+(ROTAS.RotaPlus().indexOf(l) + 1)));
			}
		}*/
	//}
    
    public static void addMarkers() {
    	if(marks.size() > 0) {
	    	for (Marker m : marks) {
	    		m.remove();
	    	}
	    	marks.clear();
	    	distmarks.clear();
    	}

    	ContextoDados db = new ContextoDados(MainActivity.context);
    	PontosCursor cursor = db.RetornarPontos();
    	for( int i=0; i <cursor.getCount(); i++)
    	{
    		cursor.moveToPosition(i);
    		marks.add(googleMap.addMarker(new MarkerOptions().position(
    				new LatLng(cursor.getlatitude(), cursor.getlongitude()))
					.title("Ponto: "+cursor.getnome())
					.snippet("Descrição: "+cursor.getdescricao())));
    		distmarks.add(dist3n);
    	}
	}
    
    public static void showPontos(){

    	ContextoDados db = new ContextoDados(MainActivity.context);
    	PontosCursor cursor = db.RetornarPontos();
    	ObjectItem[] ObjectItemData = new ObjectItem[cursor.getCount()];
    	for( int i=0; i <cursor.getCount(); i++)
    	{
    		cursor.moveToPosition(i);
    		String ponto = "Ponto: "+cursor.getnome()+"\nDescrição: "+cursor.getdescricao()+
    				"\nLatitude: "+cursor.getlatitude()+"\nLongitude: "+cursor.getlongitude()+
    				"\nData: "+cursor.getdata();
    		ObjectItemData[i] = new ObjectItem(i+1, ponto);
    	}
    	
    	// our adapter instance
        ArrayAdapterItem adapter = new ArrayAdapterItem(MainActivity.context, R.layout.list_view_row_item, ObjectItemData);

        // create a new ListView, set the adapter and item click listener
        ListView listViewItems = new ListView(MainActivity.context);
        listViewItems.setAdapter(adapter);
        listViewItems.setOnItemClickListener(new OnItemClickListenerListViewItem());

     // put the ListView in the pop up
        menu = new AlertDialog.Builder(MainActivity.context, AlertDialog.THEME_HOLO_DARK)
            .setView(listViewItems)
            .setTitle("PONTOS")
            .show();
    }
    
    public void showPopUp(){

        // add your items, this can be done programatically
        // your items can be from a database
        ObjectItem[] ObjectItemData = new ObjectItem[3];

        ObjectItemData[0] = new ObjectItem(1, "Cadastrar Ponto");
        ObjectItemData[1] = new ObjectItem(2, "Listar Pontos");
        ObjectItemData[2] = new ObjectItem(3, "Salvar Pontos");

        // our adapter instance
        ArrayAdapterItem adapter = new ArrayAdapterItem(MainActivity.context, R.layout.list_view_row_item, ObjectItemData);

        // create a new ListView, set the adapter and item click listener
        ListView listViewItems = new ListView(MainActivity.context);
        listViewItems.setAdapter(adapter);
        listViewItems.setOnItemClickListener(new OnItemClickListenerListViewItem());

        // put the ListView in the pop up
        menu = new AlertDialog.Builder(MainActivity.context, AlertDialog.THEME_HOLO_DARK)
            .setView(listViewItems)
            .setTitle("MENU PRINCIPAL")
            .show();
    }
    
    private void initilizeMap() {
        if (googleMap == null) {
            googleMap = ((MapFragment) getFragmentManager().findFragmentById(
                    R.id.map)).getMap();
 
            // check if map is created successfully or not
            if (googleMap == null) {
                Toast.makeText(getApplicationContext(),
                        "Sorry! unable to create maps", Toast.LENGTH_SHORT)
                        .show();
            }
        }
    }
    
    @Override
    protected void onResume() {
        super.onResume();
        //initilizeMap();
    }
    
	@Override
    protected void onStart() {
        super.onStart();
    }
	
	@Override
    protected void onStop() {
        super.onStop();
    }
	
	private GoogleMap.OnMyLocationChangeListener myLocationChangeListener = new GoogleMap.OnMyLocationChangeListener() {
	    @Override
	    public void onMyLocationChange(Location location) {
	    	// Getting latitude of the current location
	        double latitude = location.getLatitude();
	        // Getting longitude of the current location
	        double longitude = location.getLongitude();
	        // Creating a LatLng object for the current location
	        
	        float[] r;
	        for(int i=0; i<marks.size(); i++) {
	        	r = new float[1];
	        	Location.distanceBetween(latitude, longitude,
	                    marks.get(i).getPosition().latitude,
	                    marks.get(i).getPosition().longitude, r);
	        	
	        	if(r[0] <= dist3n && distmarks.get(i) == dist3n) {
	        		distmarks.set(i, dist2n);
	        		onClickSpeech(dist3t, marks.get(i).getTitle());
	        	} else if(r[0] <= dist2n && distmarks.get(i) == dist2n) {
	        		distmarks.set(i, dist1n);
	        		onClickSpeech(dist2t, marks.get(i).getTitle());
	        	} else if(r[0] <= dist1n && distmarks.get(i) == dist1n) {
	        		distmarks.set(i, 0.0f);
	        		onClickSpeech(dist1t, marks.get(i).getTitle());
	        	}
	        }
	   }
	};
	
	public void addListenerOnButton() {

		button = (Button) findViewById(R.id.button1);

		button.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {

			  showPopUp();

			}

		});

	}

	public void onClickSpeech(String distancia, String titulo) {
		
		textoQueSeraFalado = "a menos de "+distancia+" metros do "+titulo;
		
        Intent checkIntent = new Intent();
        checkIntent.setAction(TextToSpeech.Engine.ACTION_CHECK_TTS_DATA);
        startActivityForResult(checkIntent, INTENT_TEXT_SPEECH_CODE);
    }
	
	@Override
    public void onInit(int status) {
        if(status == TextToSpeech.SUCCESS) {
            Locale localeSelected = new Locale("pt","br");
            int available = textSpeech.isLanguageAvailable(localeSelected) ;
            atualizarStatusDisponibilidadeLocaleSelecionado(available);
            textSpeech.setLanguage(localeSelected);
            textSpeech.speak(textoQueSeraFalado, TextToSpeech.QUEUE_ADD, null);
        }
    }
	
	@Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == INTENT_TEXT_SPEECH_CODE) {
            if (resultCode == TextToSpeech.Engine.CHECK_VOICE_DATA_PASS) {
                Log.i("", "success, create the TTS instance"); 
                textSpeech = new TextToSpeech(this, this);
            } else {
                Log.i("", "missing data, install it");
                Intent installIntent = new Intent();
                installIntent.setAction(TextToSpeech.Engine.ACTION_INSTALL_TTS_DATA);
                startActivity(installIntent);
            }
        }
 
    }
	
	private void atualizarStatusDisponibilidadeLocaleSelecionado(int available) {
        switch (available) {
     
        case TextToSpeech.LANG_AVAILABLE:
        	Toast.makeText(context, "Locale suportada, mas não por país ou variante!", Toast.LENGTH_SHORT).show();
            break;
             
        case TextToSpeech.LANG_COUNTRY_AVAILABLE:
        	Toast.makeText(context, "Locale suportada pela Localidade, mas não por país ou variante!", Toast.LENGTH_SHORT).show();
            break;
             
        case TextToSpeech.LANG_COUNTRY_VAR_AVAILABLE:
        	Toast.makeText(context, "Locale suportada !", Toast.LENGTH_SHORT).show();
            break;
             
        case TextToSpeech.LANG_MISSING_DATA:
        	Toast.makeText(context, "Locale com dados faltando !", Toast.LENGTH_SHORT).show();
            break;
             
        case TextToSpeech.LANG_NOT_SUPPORTED:
        	Toast.makeText(context, "Locale nao suportada !", Toast.LENGTH_SHORT).show();
            break;
 
        default:
            break;
        }
    }
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		android.os.Process.killProcess(android.os.Process.myPid());
		super.onDestroy();
	}
	
	public static void generateTXT(){
		try {
			if(Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)) {
				File root = new File(Environment.getExternalStorageDirectory(), "AudioMaps");
				
				if (root.exists()) {
					if(root.delete())
						root.mkdirs();
				} else {
					root.mkdirs();
				}
				
				File gpxfile = new File(root, "Pontos.txt");
				FileWriter writer = new FileWriter(gpxfile);
				
				ContextoDados db = new ContextoDados(MainActivity.context);
		    	PontosCursor cursor = db.RetornarPontos();
		    	for( int i=0; i <cursor.getCount(); i++)
		    	{
		    		cursor.moveToPosition(i);
		    		String ponto = cursor.getlatitude()+";"+cursor.getlongitude()+";"+
		    					   cursor.getnome()+";"+cursor.getdescricao()+";"+
		    					   cursor.getdata();
		    		writer.append(ponto);
		    		writer.flush();
		    	}
				writer.close();
				Toast.makeText(MainActivity.context, "Pontos Atualizados em TXT", Toast.LENGTH_SHORT).show();
			} else {
				Toast.makeText(MainActivity.context, "Não foi possível salvar os pontos em TXT", Toast.LENGTH_SHORT).show();
			}
    
		} catch(IOException e) {
			Toast.makeText(MainActivity.context, "Não foi possível salvar os pontos em TXT: "+e.getMessage(), Toast.LENGTH_LONG).show();
		}
   }
}
