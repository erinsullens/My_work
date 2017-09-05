import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class Instructions extends JFrame {
    JPanel p = new JPanel();

    int numHarness;
    public Instructions(int x, Grid grid, HarnessGrid hGrid, int harness){
        setSize(400,500);
        numHarness = harness;

        p.setLayout(null);
        setLocation(1500,0);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        // preview button
        JButton preview = new JButton("Preivew Pattern");
        preview.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                grid.createArray(true);
            }
        });
        preview.setBounds(10,10,125,30);
        p.add(preview);

        // clear button
        JButton clear = new JButton("Clear Grid");
        clear.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                grid.clearGrid();
            }
        });
        clear.setBounds(142,10,90,30);
        p.add(clear);

        // saveField button

        JTextField saveField = new JTextField();
        saveField.setBounds(1,410,2,2);

        saveField.setPreferredSize(new Dimension(200,20));
        saveField.setBounds(150,55,125,20);
        p.add(saveField);

        // save button
        JButton save = new JButton("Save Pattern");
        save.setBounds(10,50,125,30);
        p.add(save);

        // file name exists label
        JLabel warningExists = new JLabel("This file name already exists. Please enter another name.");
        warningExists.setForeground(Color.red);
        warningExists.setBounds(1,20,2,4);
        warningExists.setBounds(10,80,400,30);
        p.add(warningExists);
        warningExists.setVisible(false);

        // Field is empty label
        JLabel warningEmpty = new JLabel("Please enter a file name.");
        warningEmpty.setForeground(Color.red);
        warningEmpty.setBounds(10,80,400,30);
        p.add(warningEmpty);
        warningEmpty.setVisible(false);

        // shows when file is created successfully
        JLabel fileCreated = new JLabel("Your pattern has been saved");
        fileCreated.setForeground(Color.blue);
        fileCreated.setBounds(10,80,400,30);
        p.add(fileCreated);
        fileCreated.setVisible(false);




        JButton createPattern = new JButton("Create Pattern");
        createPattern.setBounds(240,10,125,30);
        p.add(createPattern);

        HarnessButton[] hButtons = new HarnessButton[numHarness];
        int y = 150;
        int multiplyer=30;
        for(int i = 0; i< hGrid.harness; i++){
            hButtons[i] = new HarnessButton("h"+Integer.toString(i+1),i, grid,hGrid);
            hButtons[i].setBounds(10,y+multiplyer*i,100,30);
            p.add(hButtons[i]);

        }

        add(p);
        setVisible(true);

        createPattern.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                grid.createArray(false);
                try {
                    hGrid.createArray(false);
                    Pattern pattern = new Pattern(hGrid.patternArray, grid.height, grid.width, hGrid.harness, grid.harnessNumbersOnRows);
                } catch (IOException e1) {
                    e1.printStackTrace();
                }

            }
        });

        save.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                warningExists.setVisible(false);
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
                          //  fileCreated.setVisible(true);

                        } catch (IOException e1) {
                            e1.printStackTrace();
                        }
                    }
                }


            }
        });


    }


}
