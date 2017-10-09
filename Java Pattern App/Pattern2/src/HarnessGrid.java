import javax.swing.*;
import java.awt.*;

import java.util.ArrayList;

public class HarnessGrid extends JFrame {

    JPanel p = new JPanel();
    PButton[] buttons;
    char[][] patternArray;
    Grid grid;
    int height, width, windowWidth, windowHeight, harness;
    int base = 700;
    //blank grid to draw pattern on
    public HarnessGrid(int w, int h,int har){
        super("Harnesses");
        height = har;
        width = w;
        harness = har;
        windowDimentions();

        setSize(windowWidth,windowHeight);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);
        p.setLayout(new GridLayout(harness,width));
        // create buttons and add to grid
        for(int i = 0; i<harness*width; i++){
            String label;
            label = "h" + Integer.toString(i/width+1);
            buttons[i] = new PButton(label, i/width, grid, this, i%width);
            p.add(buttons[i]);
        }
        add(p);
        grid=new Grid(w,h,harness,this);
        setVisible(true);
    }
    // grid with loaded pattern
    public HarnessGrid(int w, int h, int har, String pattern, String hPattern, ArrayList<ArrayList> harnessNumsOnRow){
        super("Harnesses");
        height = h;
        width = w;
        harness = har;
        windowDimentions();
        setSize(windowWidth,windowHeight);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        setResizable(false);
        p.setLayout(new GridLayout(harness,width));
        String label = "";
        for(int i = 0; i<harness*width; i++){
            label = "h" + Integer.toString(i/width+1);
            buttons[i] = new PButton(label,i/width, grid, this, i%width);
            p.add(buttons[i]);
        }
        //add buttons and change color to saved pattern
        for(int i = 0; i<hPattern.length(); i++){
            if(hPattern.charAt(i)=='x') {
                buttons[i].setBackground(Color.black);
            }
        }
        add(p);
        grid=new Grid(w,h,harness, pattern,this, harnessNumsOnRow);
        setVisible(true);
    }

    // make an array of the pattern from the grid and store in patternArray
    public void createArray(boolean createWindow){
        patternArray = new char[width][harness];
        int counter = 0;
        for(int i = 0; i<harness; i++){
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
            new PreviewWindow(width, height, patternArray, grid, this);
        }
    }

    public void windowDimentions(){
        if(harness <5 && width<5){
            base = 500;
        }
        int hProportion = base;
        int wProportion = base;
        if(harness>width){
            hProportion = base;
            wProportion = base*width/harness;
        }
        if(width>harness){
            wProportion = base;
            hProportion = base*harness/width;
        }
        //figure out the best dimentions for grid
        buttons = new PButton[harness*width];
        int heightMultiplier = hProportion/harness;
        int widthMultiplier = wProportion/width;
        windowHeight = harness*heightMultiplier;
        windowWidth = width*widthMultiplier;
    }
}