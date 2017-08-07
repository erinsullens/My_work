import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

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
                grid.createArray(true);
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

        JButton save = new JButton("Save Pattern");
        JTextField saveField = new JTextField();
        saveField.setBounds(1,410,2,2);
        p.add(saveField);

        saveField.setPreferredSize(new Dimension(200,20));
        p.add(save);
        JLabel warningExists = new JLabel("This file name already exists. Please enter another name.");
        warningExists.setForeground(Color.red);
        warningExists.setBounds(1,20,2,4);
        p.add(warningExists);
        warningExists.setVisible(false);

        JLabel warningEmpty = new JLabel("Please enter a file name.");
        warningEmpty.setForeground(Color.red);
        warningEmpty.setBounds(1,20,2,4);
        p.add(warningEmpty);
        warningEmpty.setVisible(false);

        save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // check to see if there is a file name
                String fileName = saveField.getText();
                if(fileName.length() ==0){
                    warningEmpty.setVisible(true);

                }else {
                    warningEmpty.setVisible(false);
                    char[] temp;
                    //change any spaces to '_'
                    for (int i = 0; i < fileName.length(); i++) {
                        if (fileName.charAt(i) == ' ') {
                            temp = fileName.toCharArray();
                            temp[i] = '_';
                            fileName = new String(temp);
                        }
                    }
                    fileName = fileName + ".txt";


                    File f = new File(fileName);
                    if (f.exists()) {
                        warningExists.setVisible(true);
                    } else {
                        try {
                            warningExists.setVisible(false);
                            grid.savePattern(fileName);

                        } catch (IOException e1) {
                            e1.printStackTrace();
                        }
                    }
                }


            }
        });


        add(p);
        setVisible(true);
    }


}
