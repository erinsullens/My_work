package erinsullens.patternhelperattempt1;

import android.content.Context;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.AdapterView;
import android.view.View;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        populateListView();
        registerClickCallback();
        setupAddButton();
        setupShareButton();
        FileInputStream fileInputStream=null;
        FileOutputStream fileOutputStream= null;



    }

    private void populateListView(){
        PatternList patterns = new PatternList();
        patterns.PatternListConstructor(getFilesDir().toString());
        //NEED TO CHANGE TO FOR LOOP
        String[] list = {"","",""," ", "","","",""};
        System.out.println("patterns.size = " + patterns.patterns.size());
        for(int i = 0; i< patterns.patterns.size(); i++){
            System.out.println("patterns:"+ patterns.patterns.get(i).patternName);
            list[i] = patterns.patterns.get(i).patternName;
        }

      //  String[] list = {patterns.patterns.get(0).patternName};

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, R.layout.layout, list);
        ListView L = (ListView) findViewById(R.id.ListViewMain);
        L.setAdapter(adapter);

    }
    private void setupAddButton(){
        Button addButton = (Button)findViewById(R.id.addButton);

        View.OnClickListener myListener = new View.OnClickListener(){

            @Override
            public void onClick(View v){
                Intent startNewActivity = new Intent(MainActivity.this, AddPattern.class);
                startActivity(startNewActivity);
            }
        };
        addButton.setOnClickListener(myListener);
    }
    private void setupShareButton(){
        Button addButton = (Button)findViewById(R.id.shareButton);

        View.OnClickListener myListener = new View.OnClickListener(){

            @Override
            public void onClick(View v){
                Intent startNewActivity = new Intent(MainActivity.this, TakePhoto.class);
                startActivity(startNewActivity);
            }
        };
        addButton.setOnClickListener(myListener);
    }


    final static int ADD_ITEM_INTENT = 1; // use to signify result of adding item



    private void registerClickCallback(){

        ListView L = (ListView) findViewById(R.id.ListViewMain);
        L.setOnItemClickListener(new AdapterView.OnItemClickListener(){
            public void onItemClick(AdapterView<?> paret, View viewClicked, int position, long id){
                TextView textView = (TextView) viewClicked;
                PatternList patternList = new PatternList();
                patternList.PatternListConstructor(getFilesDir().toString());
               // System.out.println("First element in patternList: " + patternList.patterns[1].patternName);
                ArrayList<String> patternElements = new ArrayList<String>();
               // for(int i = 0; i< patternList.patterns.size(); i++) {
                //    if (patternList.patterns.get(i) != null && patternList.patterns.get(i).patternName == textView.getText().toString()) {
                        for(int j = 0; j< patternList.patterns.get(position).patternList.length; j++){
                            patternElements.add(j, patternList.patterns.get(position).patternList[j]);
                        }
                 //   }
              //  }
                for(int i = 0; i< patternElements.size(); i++){
                    System.out.println(patternElements.get(i));
                }
                Intent startNewActivity = new Intent(MainActivity.this, ShowPattern.class);
                startNewActivity.putStringArrayListExtra("p", patternElements);
                startActivity(startNewActivity);
            }
        });
    }




}
