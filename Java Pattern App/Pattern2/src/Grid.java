import javax.swing.*;
import java.awt.*;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Grid extends JFrame {
    JPanel p = new JPanel();
    PButton[] buttons;
    char[][] patternArray;
    Controls instructions;
    int height, width, windowWidth, windowHeight, numHarness, heightMultiplier, widthMultiplier;
    int base = 700;
    char[] harnessPattern;
    char[] harnessToRemove;
    int currentStep = -1;
    ArrayList<ArrayList> harnessNumbersOnRows;
    ArrayList<Step> steps = new ArrayList<Step>();
    HarnessGrid harnessGrid;
    int harnessNumber;
    //blank grid to draw pattern on
    public Grid(int w, int h, int harness, HarnessGrid hGrid){
        super("Pattern");
        setLocation(900,0);
        harnessGrid = hGrid;
        height = h;
        width = w;
        numHarness = harness;
        harnessPattern = new char[width];
        harnessNumbersOnRows = new ArrayList<ArrayList>();
        for(int i = 0; i<height; i++){
            harnessNumbersOnRows.add(new ArrayList<Integer>());
        }
        for(int i = 0; i< width; i++){
            harnessPattern[i] = 'o';
        }
        windowDimensions();
        setSize(windowWidth,windowHeight);
        instructions = new Controls(width*widthMultiplier,this, hGrid, harness);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);
        p.setLayout(new GridLayout(height,width));
        // create buttons and add to grid
        for(int i = 0; i<height*width; i++){
            buttons[i] = new PButton("", i/width, this, hGrid, i);
            buttons[i].canColor = false;
            p.add(buttons[i]);
        }
        add(p);
        setVisible(true);
    }
    // grid with loaded pattern
    public Grid(int w, int h, int harness, String pattern, HarnessGrid hGrid, ArrayList<ArrayList> harnessNumsOnRow){
        super("Pattern");
        harnessGrid = hGrid;
        height = h;
        width = w;
        numHarness = harness;
        harnessNumbersOnRows = harnessNumsOnRow;
        int base = 700;
        harnessPattern = new char[width];
        harnessToRemove = new char[width];
        windowDimensions();
        setSize(windowWidth,windowHeight);
        instructions = new Controls(width*widthMultiplier,this, hGrid, harness);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setResizable(false);
        p.setLayout(new GridLayout(height,width));

        for(int i = 0; i<height*width; i++){
            int row = i/width;
            int col = i%width;
            buttons[i] = new PButton("", row, this, hGrid, col);
            buttons[i].canColor = false;
            p.add(buttons[i]);
        }
        //add buttons and change color to saved pattern
        for(int i = 0; i<pattern.length(); i++){
            if(pattern.charAt(i)=='x') {
                buttons[i].setBackground(Color.black);
            }
        }
        add(p);
        setVisible(true);
    }
    // make an array of the pattern from the grid and store in patternArray
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
            new PreviewWindow(width, height, patternArray, this, harnessGrid);
        }
    }
    //print 2D array
    public void print2DArray(char[][] array){
        for(int i = 0; i<height; i++){
            for(int j = 0; j<width; j++){

                System.out.print(array[j][i]+" ");
            }
            System.out.println("");
        }
    }

    // function called by button to clear grid
    public void clearGrid(){
        for(int i = 0; i< height*width;i++){
            buttons[i].setBackground(Color.white);
        }
        for(int i = 0; i< harnessNumbersOnRows.size(); i++){
            harnessNumbersOnRows.get(i).clear();
        }
    }
    // save pattern to file to be loaded later
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
            String dimention = "w: "+ Integer.toString(width)+ '\n'+ "h: "+ Integer.toString(height)+'\n'+ "s: "+ Integer.toString(numHarness)+'\n';

            out.write(dimention);

            for(int i = 0; i<height; i++){
                for(int j = 0; j<width; j++){
                    out.write(Character.toString(patternArray[j][i]) );
                    out.write(" ");
                }
                out.write('\n');
            }
            out.write("harnessGrid:"+'\n');
            harnessGrid.createArray(false);
            for(int i = 0; i<numHarness; i++){
                for(int j = 0; j<width; j++){
                    out.write(Character.toString(harnessGrid.patternArray[j][i]) );
                    out.write(" ");
                }
                out.write('\n');
            }

            out.write("HarnessNumbers:"+'\n');
            for(int i = 0; i< harnessNumbersOnRows.size(); i++){
                for(int j = 0; j< harnessNumbersOnRows.get(i).size(); j++){
                    out.write(Integer.toString((Integer) harnessNumbersOnRows.get(i).get(j)));
                    if(j!= harnessNumbersOnRows.get(i).size()-1){
                        out.write(",");
                    }
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
    public void colorRow(int row) {
        int indexOfButton = row * width;
        for (int i = 0; i < width; i++) {
            if (harnessPattern[i] == 'x') {
                buttons[indexOfButton + i].setBackground(Color.black);
            }
        }
        boolean harnessExists = false;
        for (int i = 0; i < harnessNumbersOnRows.get(row).size(); i++) {
            if (harnessNumbersOnRows.get(row).get(i).equals(new Integer(harnessNumber))) {
                harnessExists = true;
            }
        }
        if (!harnessExists) {
            harnessNumbersOnRows.get(row).add(new Integer(harnessNumber));
            char[] temp = new char[width];
            for(int i = 0; i<width; i++){
                temp[i] = harnessPattern[i];
            }
            int h = harnessNumber;
            steps.add(new Step(row,temp,h));

        }
    }

    public void undoHarnessOnRow() {
        int indexOfButton = steps.get(steps.size()-1).rowOnGrid * width;
        int row = steps.get(steps.size()-1).rowOnGrid;
        for (int i = 0; i < width; i++) {
            if (steps.get(steps.size()-1).harnessPattern[i] == 'x') {
                buttons[indexOfButton + i].setBackground(Color.white);
            }
        }
        for (int i = 0; i < harnessNumbersOnRows.get(row).size(); i++) {
            if (harnessNumbersOnRows.get(row).get(i).equals(new Integer(steps.get(steps.size()-1).harness))) {
                harnessNumbersOnRows.get(row).remove(i);
                steps.remove(steps.size()-1);

            }
        }
    }

    public void colorOneSquare(int row, int col){
        int indexOfButton = row*width+col;
        if(buttons[indexOfButton].getBackground().equals(Color.black)){
            buttons[indexOfButton].setBackground(Color.white);
        }
        else{
            buttons[indexOfButton].setBackground(Color.black);
        }
    }
    // called whenever a button on the harness grid is pressed
    public void redoColor(int row, int column){
        for(int i = 0; i<harnessNumbersOnRows.size(); i++){
            for(int j = 0; j<harnessNumbersOnRows.get(i).size(); j++){
                if (harnessNumbersOnRows.get(i).get(j).equals(new Integer(row))) {
                    colorOneSquare(i,column);
                }
            }
        }
    }
    public void windowDimensions(){
        if(height <5 && width<5){
            base = 500;
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
        //figure out the best dimentions for grid
        buttons = new PButton[height*width];
        heightMultiplier = hProportion/height;
        widthMultiplier = wProportion/width;
        windowHeight = height*heightMultiplier;
        windowWidth = width*widthMultiplier;
    }
}