import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class HarnessButton extends JButton implements ActionListener{
    int harnessNum;
    HarnessGrid harnessGrid;
    Grid grid;


    public HarnessButton(String label, int harnessNumber, Grid g, HarnessGrid hGrid){
        this.addActionListener(this);
        grid = g;
        this.setBackground(Color.white);
        this.setText(label);
        harnessNum = harnessNumber;
        harnessGrid = hGrid;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        char[] harnessPattern;
        harnessGrid.createArray(false);
        grid.createArray(false);
        for(int i = 0; i< grid.width; i++) {
            grid.harnessPattern[i] = harnessGrid.patternArray[i][harnessNum];
        }
        grid.harnessNumber = harnessNum;

    }
}