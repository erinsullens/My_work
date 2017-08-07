import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;


public class Grid extends JFrame {

    JPanel p = new JPanel();
    PButton[] buttons;
    char[][] patternArray;
    Instructions instructions;
    Grid drawPattern;
    JPanel i = new JPanel();
    int height;
    int width;
    int windowWidth;
    int windowHeight;
    int harness;



    public Grid(int w, int h, int harness){

        super("Pattern");
        height = h;
        width = w;

        int base = 1000;
        if(height <5 && width<5){
            base = 700;
        }

        int hProportion = base;
        int wProportion = base;
        if(height>width){
            hProportion = base;
            wProportion = base*width/height;
        }
        if(width>height){
            wProportion = base;
            hProportion = base*height/width;
        }
        buttons = new PButton[height*width];
        int heightMultiplier = hProportion/height;
        int widthMultiplier = wProportion/width;
        windowHeight = height*heightMultiplier;
        windowWidth = width*widthMultiplier;
        setSize(windowWidth,windowHeight);
        instructions = new Instructions(width*widthMultiplier,this);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setResizable(false);
        p.setLayout(new GridLayout(height,width));

        for(int i = 0; i<height*width; i++){
            buttons[i] = new PButton("");

            p.add(buttons[i]);
        }

       // p.add(preview);
        add(p);




        setVisible(true);
    }

    public Grid(int w, int h, int harness, String pattern){


        super("Pattern");
        height = h;
        width = w;

        int base = 1000;
        if(height <5 && width<5){
            base = 700;
        }

        int hProportion = base;
        int wProportion = base;
        if(height>width){
            hProportion = base;
            wProportion = base*width/height;
        }
        if(width>height){
            wProportion = base;
            hProportion = base*height/width;
        }
        buttons = new PButton[height*width];
        int heightMultiplier = hProportion/height;
        int widthMultiplier = wProportion/width;
        windowHeight = height*heightMultiplier;
        windowWidth = width*widthMultiplier;
        setSize(windowWidth,windowHeight);
        instructions = new Instructions(width*widthMultiplier,this);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setResizable(false);
        p.setLayout(new GridLayout(height,width));

        for(int i = 0; i<height*width; i++){
            buttons[i] = new PButton("");

            p.add(buttons[i]);
        }

        for(int i = 0; i<pattern.length(); i++){

            if(pattern.charAt(i)=='x') {
                buttons[i].setBackground(Color.black);

            }


        }

        // p.add(preview);
        add(p);




        setVisible(true);
    }



    public void createArray(boolean createWindow){
        patternArray = new char[width][height];
        int counter = 0;
        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){
                if(buttons[counter].getBackground().equals(Color.black)){
                    patternArray[j][i] = 'x';
                }else{
                    patternArray[j][i] = 'o';
                }
                counter++;
            }
        }
        if(createWindow) {
            new PreviewWindow(width, height, patternArray);
        }
       // print2DArray(patternArray);

    }
    public void print2DArray(char[][] array){
        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){

                System.out.print(array[j][i]+" ");
            }
            System.out.println("");
        }
    }

    public void clearGrid(){
        for(int i = 0; i< height*width;i++){
            buttons[i].setBackground(Color.white);
        }
    }

    public void savePattern(String fileName) throws IOException {
        createArray(false);


        BufferedWriter out = null;
        BufferedWriter outSaved = null;
        try
        {
            FileWriter savedWriter = new FileWriter("savedPatterns.txt", true);
            outSaved = new BufferedWriter(savedWriter);
            outSaved.write(fileName+'\n');
            FileWriter fstream = new FileWriter(fileName, true); //true tells to append data.
            out = new BufferedWriter(fstream);
            String dimention = "w: "+ Integer.toString(width)+ '\n'+ "h: "+ Integer.toString(height)+'\n';

            out.write(dimention);
            for(int i = 0; i<height; i++){
                for(int j = 0; j<width; j++){
                    out.write(Character.toString(patternArray[j][i]) );
                    out.write(" ");

                }
                out.write('\n');


            }
        }
        catch (IOException e)
        {
            System.err.println("Error: " + e.getMessage());
        }
        finally
        {
            if(out != null) {
                out.close();
                outSaved.close();
            }
        }

    }


// working on preview window
}