package erinsullens.patternhelperattempt1;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.ArrayList;
import java.util.Scanner;

import android.app.Activity;
import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

/**
 * Created by erinsullens on 4/26/16.
 */
public class PatternList extends Activity {

    ArrayList<Pattern> patterns = new ArrayList<Pattern>();
    public int patternListIterator = 0;


    public void PatternListConstructor(String filePath) {
        String[] sample1 = {"1","2","3","4"};
        patterns.add(patternListIterator, new Pattern("Sample1",sample1));
        patternListIterator++;


        //make sure that patterns.txt is created
        FileInputStream fileInputStream=null;
        FileOutputStream fileOutputStream= null;
//
//        try {
//
//
//            new FileOutputStream("patterns.txt", true).close();
//            String filler = " ";
//            fileOutputStream = openFileOutput("patterns.txt", Context.MODE_PRIVATE);
//            fileOutputStream.write(filler.getBytes());
//            fileOutputStream.flush();
//
//
//        }catch(FileNotFoundException e) {
//            //TODO Auto-generated catch block
//            e.printStackTrace();
//
//        }catch(IOException e){
//            //TODO Auto-generated catch block
//            e.printStackTrace();
//        }
//        finally{
//            try{
//                if(fileOutputStream!= null) {
//                    fileOutputStream.close();
//                }
//            }catch(IOException e){
//                //TODO Auto-generated catch block
//                e.printStackTrace();
//            }
//        }

        //Now read from patterns.txt

            String line = null;
//            new FileInputStream("patterns.txt").close();
//            fileInputStream = openFileInput("patterns.txt");
            //  InputStreamReader inStreamReaderObject = new InputStreamReader(fileInputStream);
        try {


            File logfile = new File(filePath, "patterns.txt");
           // Log.v("filelocation", logfile.getCanonicalPath());
           // logfile.delete();
            if(!logfile.exists()) {
                FileWriter writer = new FileWriter(logfile,true);
                writer.write("Sample2 1 2 3 4 5 6 7 9 9 9\n");
             //   writer.write(System.getProperty("line.separator"));
                writer.flush();
                writer.close();
            }

            long length = logfile.length();
            System.out.println("size of file: " + length);


        }catch(FileNotFoundException e) {
            //TODO Auto-generated catch block
            e.printStackTrace();

        }catch(IOException e){
            //TODO Auto-generated catch block
            e.printStackTrace();
        }
        finally{
//            try{
//                if(fileOutputStream!= null) {
//                    fileOutputStream.close();
//                }
//            }catch(IOException e){
//                //TODO Auto-generated catch block
//                e.printStackTrace();
//            }
        }

            try {

                Scanner scan = new Scanner(new File(filePath + "/patterns.txt"));

                System.out.println("hasnextline: " + scan.hasNextLine());
                while (scan.hasNextLine()) {
                    line = scan.nextLine();
                    System.out.println("line: " + line);
                    String[] result;
                    //if(line!=null) {
                    result = line.split(" ");
                    //}
                    String name = "";
                    // result[0] = "";
                    System.out.println("result: " + result[0]);
                    name = result[0];

                    String[] patternSteps = new String[result.length - 1];
                    for (int i = 0; i < result.length - 1; i++) {
                        patternSteps[i] = result[i + 1];
                    }
                    patterns.add(patternListIterator, new Pattern(name, patternSteps));
                    System.out.println("Size of pattern: " + patternSteps.length);
                    for (int i = 0; i < patternSteps.length; i++) {
                        System.out.println("PatternSteps: " + patternSteps[i]);
                    }
                    patternListIterator++;
                }


            }catch(FileNotFoundException e){
                //TODO Auto-generated catch block
                e.printStackTrace();
            }catch(IOException e){
                e.printStackTrace();
            }
        for(int i = 0; i<2; i++){
            System.out.println("first step in each pattern: "+ patterns.get(i).patternList[1]);
        }



            String[] sample5 = {"1", "2", "3", "4"};
//        patterns.add(patternListIterator, new Pattern("Samepla",sample1));
        }

    public void addPattern(Pattern pattern){
        patterns.add(patternListIterator, pattern);
        patternListIterator++;
    }



}