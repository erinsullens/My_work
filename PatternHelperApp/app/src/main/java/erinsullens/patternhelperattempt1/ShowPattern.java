package erinsullens.patternhelperattempt1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.ArrayList;

public class ShowPattern extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        ListView listView;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_show_pattern);
        Bundle extras = getIntent().getExtras();
        ArrayList<String> p = extras.getStringArrayList("p");
//        ArrayList<String> p = new ArrayList<String>();
//        p.add("1");
//        p.add("2");
//        p.add("3");
        populateListView(p);



    }


    private void populateListView(ArrayList<String> p){
        int j = 0;
        int size = 0;

        while(p.get(j)!=null){
            size++;
            j++;
        }
        String[] listOfElements = new String[size];
        for(int i = 0; i < size; i++){
            if(p.get(i)!= null) {
                listOfElements[i] = p.get(i);
            }
        }
        for(int i = 0; i < size; i++) {
            System.out.println("listOfElements: "+listOfElements[i]);
        }
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.text, listOfElements);
        ListView L = (ListView) findViewById(R.id.listView);
        L.setAdapter(adapter);
        L.setOnItemClickListener(new AdapterView.OnItemClickListener(){
            public void onItemClick(AdapterView<?> paret, View viewClicked, int position, long id){
                viewClicked.setSelected(true);

            }
        });
    }

}
