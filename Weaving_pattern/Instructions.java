import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Instructions extends JFrame {
    JPanel p = new JPanel();
    public Instructions(int x, Grid grid){
        setSize(400,400);
        setLocation(x,0);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        // preview button
        JButton preview = new JButton("Preivew Pattern");
        preview.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                grid.createArray();
            }
        });
        p.add(preview);
        // clear button
        JButton clear = new JButton("Clear Grid");
        clear.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                grid.clearGrid();
            }
        });
        p.add(clear);


        add(p);
        setVisible(true);
    }


}
