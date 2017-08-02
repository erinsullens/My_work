import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
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

    public static void main(String args[]){
        new Grid();

    }

    public Grid(){

        super("Pattern");
        Scanner reader = new Scanner(System.in);
        System.out.println("Please enter the desired height for the grid");
        height = reader.nextInt();
        System.out.println("Please enter the desired width for the grid");
        width = reader.nextInt();
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

    public void createArray(){
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
        new PreviewWindow(width, height,patternArray);
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


// working on preview window
}