package erinsullens.patternhelperattempt1;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

/**
 * Created by erinsullens on 5/4/16.
 */
public class AddPattern extends AppCompatActivity{

    EditText name, ps;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_pattern);

        Button btnOk = (Button) (this.findViewById(R.id.btnOK));
        btnOk.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                validateSaveExit();
            }
        });
        name = (EditText) findViewById(R.id.pn);
        ps = (EditText) findViewById(R.id.steps);

    }

    private String checkNonEmpty(int id, String info) {
        TextView textView = (TextView) (findViewById(id));
        if (textView != null) {
            CharSequence txt = textView.getText();
            if (txt != null) {
                int len = txt.length();
                if (len > 0) {
                    return txt.toString();
                }
            }
            textView.setHint(info + " is required");
        }
        Toast.makeText(this, info + " is required", Toast.LENGTH_SHORT).show();
        return null;
    }

    private void validateSaveExit() {

        String patternName = checkNonEmpty(R.id.pn, "Pattern Name");
        String patternSteps = checkNonEmpty(R.id.steps, "Pattern");

        if (patternName != null && patternSteps !=null ) {
            //add new pattern to file
            String patternNameToSave = name.getText().toString();
            String patternStepsToSave = ps.getText().toString();
            patternNameToSave = patternNameToSave +" ";
          //  FileOutputStream fileOutputStream=null;
            File file = null;
            try {
              //  new FileOutputStream("patterns.txt", true).close();

                file=getFilesDir();
                File logfile = new File(getFilesDir(), "patterns.txt");
                FileWriter writer = new FileWriter(logfile,true);
                BufferedWriter out = new BufferedWriter(writer);
                out.write(patternNameToSave + patternStepsToSave + "\n");
                writer.flush();
                out.close();
                writer.close();
              //  myFile.write(patternStepsToSave);
//                myFile.write(System.getProperty("line.separator"));


//                fileOutputStream = openFileOutput("patterns.txt", Context.MODE_APPEND);
//                fileOutputStream.write(patternNameToSave.getBytes());
//                fileOutputStream.write(patternStepsToSave.getBytes());
//                fileOutputStream.write(System.getProperty("line.separator").getBytes());
//                fileOutputStream.flush();
                System.out.println("File location: " + file.toString() + "/patterns.txt");
                System.out.println("This should print out patterns.txt");

                Scanner scan = new Scanner(new File(getFilesDir() + "/patterns.txt"));
                String line = null;
                System.out.println("has next line after adding: "+ scan.hasNextLine());
                while(scan.hasNextLine()){
                    line = scan.nextLine();
                    System.out.println("Lines of new pattern: "+line);
                }



            }catch(FileNotFoundException e){
                //TODO Auto-generated catch block
                e.printStackTrace();
            }catch(IOException e){
                //TODO Auto-generated catch block
                e.printStackTrace();
            }




        }
        Intent startNewActivity = new Intent(AddPattern.this, MainActivity.class);
        startActivity(startNewActivity);

    }
}
