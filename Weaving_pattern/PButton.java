import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class PButton extends JButton implements ActionListener{
    ImageIcon b,w;
    boolean canColor = true;

    public PButton(String label){
        this.addActionListener(this);
        this.setBackground(Color.white);
        this.setLabel(label);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (canColor) {
            if (this.getBackground().equals(Color.white)) {
                this.setBackground(Color.black);
            } else {
                this.setBackground(Color.white);
            }
        }
    }
}
