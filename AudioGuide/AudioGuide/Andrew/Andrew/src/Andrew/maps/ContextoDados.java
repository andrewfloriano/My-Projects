package Andrew.maps;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteCursor;
import android.database.sqlite.SQLiteCursorDriver;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteQuery;
import android.util.Log;
import android.widget.Toast;

public class ContextoDados extends SQLiteOpenHelper {

	/** O nome do arquivo de base de dados no sistema de arquivos */
	private static final String NOME_BD = "Andrew";
	/** A versão da base de dados que esta classe compreende. */
	private static final int VERSAO_BD = 2;
	private static final String LOG_TAG = "Andrew";
	/** Mantém rastreamento do contexto que nós podemos carregar SQL */
	private final Context contexto;

	private static final String DICTIONARY_TABLE_CREATE =
            "CREATE TABLE pontos (" +
            " id INTEGER PRIMARY KEY AUTOINCREMENT, " +
            " nome TEXT," +
            " descricao TEXT," +
            " data TEXT," +
            " latitude REAL, " +
            " longitude REAL);";
	
	public ContextoDados(Context context) {
		super(context, NOME_BD, null, VERSAO_BD);
		this.contexto = context;
		}

	@Override
	public void onCreate(SQLiteDatabase db)
	{
		db.beginTransaction();

		try
		{
			// Cria a tabela e testa os dados
			ExecutarComandosSQL(db, DICTIONARY_TABLE_CREATE);
			db.setTransactionSuccessful();
		}
		catch (SQLException e)
		{
			Log.e("Erro ao criar as tabelas e testar os dados", e.toString());
		}
		finally
		{
			db.endTransaction();
		}
	}

	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion)
	{
		Log.w(LOG_TAG, "Atualizando a base de dados da versão " + oldVersion + " para " + newVersion + ", que destruirá todos os dados antigos");
		db.beginTransaction();

		try
		{
			ExecutarComandosSQL(db, DICTIONARY_TABLE_CREATE);
			db.setTransactionSuccessful();
		}
		catch (SQLException e)
		{
			Log.e("Erro ao atualizar as tabelas e testar os dados", e.toString());
			throw e;
		}
		finally
		{
			db.endTransaction();
		}

		// Isto é apenas didático. Na vida real, você terá de adicionar novas colunas e não apenas recriar o mesmo banco
		onCreate(db);
	}

	/**
	* Executa todos os comandos SQL passados no vetor String[]
	* @param db A base de dados onde os comandos serão executados
	* @param sql Um vetor de comandos SQL a serem executados
	*/
	private void ExecutarComandosSQL(SQLiteDatabase db, String[] sql)
	{
		for( String s : sql )
			if (s.trim().length()>0)
				db.execSQL(s);
	}
	
	private void ExecutarComandosSQL(SQLiteDatabase db, String sql)
	{
		db.execSQL(sql);
	}

	/** Retorna um ContatosCursor ordenado
	* @param critério de ordenação
	*/
	public PontosCursor RetornarPontos()
	{
		String sql = PontosCursor.CONSULTA;
		SQLiteDatabase bd = getReadableDatabase();
		PontosCursor cc = (PontosCursor) bd.rawQueryWithFactory(new PontosCursor.Factory(), sql, null, null);
		cc.moveToFirst();
		return cc;
	}

	public long InserirPonto(String nome, String descricao, String data, double latitude, double longitude)
	{
		SQLiteDatabase db = getReadableDatabase();

		try
		{
			ContentValues initialValues = new ContentValues();
			initialValues.put("nome", nome);
			initialValues.put("descricao", descricao);
			initialValues.put("data", data);
			initialValues.put("latitude", latitude);
			initialValues.put("longitude", longitude);
			return db.insert("pontos", null, initialValues);
		}
		finally
		{
			db.close();
		}
	}

	public Context getContexto() {
		return contexto;
	}

	public static class PontosCursor extends SQLiteCursor
	{
		private static final String CONSULTA = "SELECT * FROM pontos order by id desc";
		
		@SuppressWarnings("deprecation")
		public PontosCursor(SQLiteDatabase db, SQLiteCursorDriver driver,
				String editTable, SQLiteQuery query) {
			super(db, driver, editTable, query);
			// TODO Auto-generated constructor stub
		}

		private static class Factory implements SQLiteDatabase.CursorFactory
		{
			@Override
			public Cursor newCursor(SQLiteDatabase db, SQLiteCursorDriver driver, String editTable, SQLiteQuery query)
			{
				return new PontosCursor(db, driver, editTable, query);
			}
		}

		public String getnome()
		{
			return getString(getColumnIndexOrThrow("nome"));
		}
		
		public String getdescricao()
		{
			return getString(getColumnIndexOrThrow("descricao"));
		}
		
		public String getdata()
		{
			return getString(getColumnIndexOrThrow("data"));
		}

		public double getlatitude()
		{
			return getDouble(getColumnIndexOrThrow("latitude"));
		}

		public double getlongitude()
		{
			return getDouble(getColumnIndexOrThrow("longitude"));
		}
	}
}