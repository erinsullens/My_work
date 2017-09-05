import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Pattern {

    char[][] harnessArray;
    ArrayList<ArrayList> harnessesOnRows;
    int harness;
    int height;
    int width;


    public Pattern(char[][] pattern, int h, int w, int har, ArrayList<ArrayList> list) throws IOException {
        height = h;
        width = w;
        harnessArray = pattern;
        harnessesOnRows = list;
        harness = har;
        computePattern();

    }

    public void print2DArray(char[][] array){
        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){

                System.out.print(array[j][i]+" ");
            }
            System.out.println("");
        }
    }

    // create instructions for warping and weaving a pattern into a text document
    public void computePattern() throws IOException {
        BufferedWriter out = null;
        FileWriter fstream = new FileWriter("pattern.txt", false); //true tells to append data.
        out = new BufferedWriter(fstream);
        String p = "";

        for(int i = 0; i<harness; i++){
           // p = p+"   ";
            for(int j = 0; j<width; j++){
                if(harnessArray[j][i]=='o'){
                    p = p+"   ";
                }
                else{
                    p = p+ Integer.toString(i+1);
                }

            }
            p+= '\n';
            for(int x = 0; x<width*4-10; x++){
                p+="-";
            }
            p+='\n';
        }

        p+="Weaving instructions:"+'\n';

        for(int i = height-1; i>=0; i--){
            for(int j = 0; j<harnessesOnRows.get(i).size(); j++){
                p+= Integer.toString((Integer) harnessesOnRows.get(i).get(j)+1);
                if(j+1!= harnessesOnRows.get(i).size()){
                    p+=",";
                }
            }
            p+='\n';

        }


        out.write(p);



        out.close();

    }
}
