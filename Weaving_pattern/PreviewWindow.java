import javax.swing.*;
import java.awt.*;


public class PreviewWindow extends JFrame {

    JPanel p = new JPanel();
    PButton[] buttons;
    int base;

    public PreviewWindow(int width, int height, char[][] array){
        base = 1000;
        int wOriginal = width;
        int hOriginal = height;
        width = width*5;
        height = height*4;
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
        int windowHeight = height*heightMultiplier;
        int windowWidth = width*widthMultiplier;
        setSize(windowWidth,windowHeight);
        p.setLayout(new GridLayout(height,width));


        // working on array to preview - do rows over and over
        int counter = 0;
        for(int x = 0; x<4; x++) {
            for (int i = 0; i < wOriginal; i++) {
                for(int y = 0; y <5; y++) {
                    for (int j=0; j < hOriginal; j++) {
                        buttons[counter] = new PButton("");
                        buttons[counter].canColor = false;
                        if(array[i][j]=='x'){
                            buttons[counter].setBackground(Color.black);
                        }
                        p.add(buttons[counter]);
                        counter++;
                    }
                }

            }
        }
        add(p);
        setVisible(true);
    }
}
/*

y = i/width;
            x = i%width;
            buttons[i] = new PButton("");
            buttons[i].canColor = false;
//            if(array[x][y]=='x'){
//                buttons[i].setBackground(Color.black);
//            }
            p.add(buttons[i]);
 */