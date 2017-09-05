import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PButton extends JButton implements ActionListener{
    ImageIcon b,w;
    boolean canColor = true;
    int rowToColor;
    HarnessGrid h;
    Grid g;

    public PButton(String label, int row, Grid grid, HarnessGrid hGrid){
        this.addActionListener(this);
        this.setBackground(Color.white);
        this.setText(label);
        rowToColor = row;
        g = grid;
        h = hGrid;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // action for buttons in harness grid
        if (canColor) {
            if (this.getBackground().equals(Color.white)) {
                this.setBackground(Color.black);
                h.grid.redoColor(rowToColor);

            } else {
                this.setBackground(Color.white);

                h.grid.redoColor(rowToColor);
            }
        }
        // action for buttons in pattern grid
        else {
            g.createArray(false);
            g.colorRow(rowToColor);
        }
    }
}
