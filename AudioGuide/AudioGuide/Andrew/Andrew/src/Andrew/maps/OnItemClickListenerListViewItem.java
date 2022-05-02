package Andrew.maps;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import Andrew.maps.R;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.location.Location;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class OnItemClickListenerListViewItem implements OnItemClickListener {

	private Context context = null;
	
    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        context = view.getContext();
        TextView textViewItem = ((TextView) view.findViewById(R.id.textViewItem));
        String listItemId = textViewItem.getTag().toString();
        executar(listItemId);
    }
    
    private void executar(String ItemId){
    	if(ItemId.equals("1")) {
    		if(MainActivity.googleMap.getMyLocation() != null) {	    		
				LayoutInflater li = LayoutInflater.from(context);
				View promptsView = li.inflate(R.layout.prompts, null);
				AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
						context);
				alertDialogBuilder.setView(promptsView);
				final EditText userInput = (EditText) promptsView
						.findViewById(R.id.editTextDialogUserInput);
				final EditText userInput2 = (EditText) promptsView
						.findViewById(R.id.editTextDialogUserInput2);
				final EditText userInput3 = (EditText) promptsView
						.findViewById(R.id.editTextDialogUserInput3);
				final EditText userInput4 = (EditText) promptsView
						.findViewById(R.id.editTextDialogUserInput4);
				
				Location l = MainActivity.googleMap.getMyLocation();
				userInput3.setText(String.valueOf(l.getLatitude()));
				userInput4.setText(String.valueOf(l.getLongitude()));
				
				alertDialogBuilder
					.setCancelable(false)
					.setPositiveButton("OK",
					  new DialogInterface.OnClickListener() {
					    public void onClick(DialogInterface dialog,int id) {
					    	if(userInput.getText().length() > 0) {
					    		SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy");
					            Date data = new Date();
					            Calendar  cal = Calendar.getInstance();
					            cal.setTime(data);
					            Date data_atual = cal.getTime();
					            String data_completa = dateFormat.format(data_atual);
					    		ContextoDados db = new ContextoDados(MainActivity.context);
					    		db.InserirPonto(userInput.getText().toString(), userInput2.getText().toString(), data_completa, Double.valueOf(userInput3.getText().toString()), Double.valueOf(userInput4.getText().toString()));
					    		Toast.makeText(context, "Ponto Cadastrado com Sucesso!", Toast.LENGTH_SHORT).show();
					    		MainActivity.addMarkers();
					    	}
					    }
					  })
					.setNegativeButton("Cancel",
					  new DialogInterface.OnClickListener() {
					    public void onClick(DialogInterface dialog,int id) {
						dialog.cancel();
					    }
					  });
				AlertDialog alertDialog = alertDialogBuilder.create();
				alertDialog.show();
    		} else
    			Toast.makeText(context, "Posição Atual Desconhecida", Toast.LENGTH_SHORT).show();
    	} else if(ItemId.equals("2")) {
    		MainActivity.showPontos();
    	} else if(ItemId.equals("3")) {
    		MainActivity.generateTXT();
    	}
    }
}