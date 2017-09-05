import com.sun.org.apache.bcel.internal.generic.ARRAYLENGTH;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusListener;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class FirstWindow extends JFrame {

    JPanel p = new JPanel();
    static int width;
    static int height;
    static int harness;
    JComboBox<String> saved;
    // first window that appears in the program. User input is the dimensions for grid, or load pattern
    public FirstWindow() throws FileNotFoundException {
        setSize(500, 300);
        p.setLayout(null);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        BufferedReader read = new BufferedReader(new FileReader("savedPatterns.txt"));

        ArrayList<String> savedPatterns = new ArrayList<String>();
        String line;
        try {
            while ((line = read.readLine()) != null) {
                savedPatterns.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }



        JLabel widthLabel = new JLabel("Width of grid:");
        widthLabel.setBounds(10,10,90,20);
        p.add(widthLabel);

        JTextField widthField = new JTextField();
        widthField.setBounds(95,10,50,20);
        p.add(widthField);



        JLabel harnessLabel = new JLabel("Number of harnesses:");
        harnessLabel.setBounds(10,50,130,20);
        p.add(harnessLabel);

        JTextField harnessField = new JTextField();
        harnessField.setBounds(150,50,50,20);
        p.add(harnessField);
        harnessField.setPreferredSize(new Dimension(50, 20));

        JLabel heightLabel = new JLabel("Height of grid:");
        heightLabel.setBounds(180,10,90,20);
        p.add(heightLabel);

        JTextField heightField = new JTextField();
        heightField.setBounds(260,10,50,20);
        p.add(heightField);
        heightField.setPreferredSize(new Dimension(50, 20));

        JButton create = new JButton("Continue");
        create.setBounds(225,50,100,20);
        p.add(create);

        JLabel warning = new JLabel("Height, width, and number of harnesses all need to be an integer greater than 0");
        warning.setForeground(Color.red);
        warning.setBounds(1, 20, 2, 4);
        warning.setBounds(10,80,450,20);
        p.add(warning);
        warning.setVisible(false);

        String[] s = new String[savedPatterns.size()];
        for(int i = 0; i< savedPatterns.size(); i++){
            s[i] = savedPatterns.get(i);
            s[i] = s[i].substring(0,s[i].length()-4);
        }

        saved = new JComboBox<String>(s);
        saved.setPreferredSize(new Dimension(100,20));
        saved.setBounds(10,200,100,20);
        p.add(saved);



        JButton load = new JButton("Load Saved Pattern");
        load.setBounds(120,200,150,20);
        p.add(load);
        load.setVisible(true);

        load.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    loadSaved();
                } catch (FileNotFoundException e1) {
                    e1.printStackTrace();
                }
            }
        });

        create.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                String w = widthField.getText();
                String h = heightField.getText();
                String har = harnessField.getText();
                if (isInteger(w) && isInteger(h) && isInteger(har)) {
                    width = Integer.parseInt(w);
                    height = Integer.parseInt(h);
                    harness = Integer.parseInt(har);
                    createGrid();
                    warning.setVisible(false);

                } else {
                    warning.setVisible(true);
                }


            }
        });


        add(p);
        setVisible(true);
    }



    public static void main(String args[]) throws FileNotFoundException {
        new FirstWindow();

    }
    public void createGrid(){

        new HarnessGrid(width, height, harness);

    }

    public boolean isInteger(String s){
        if(s.isEmpty()) return false;
        if(s.length()==1 && s.charAt(0)=='0') return false;
        for(int i = 0; i<s.length(); i++){
            if(Character.digit(s.charAt(i),10)<0){
                return false;
            }
        }

        return true;


    }
    // load saved pattern
    public void loadSaved() throws FileNotFoundException {
        String file = (String)saved.getSelectedItem();
        file = file + ".txt";
        int width = 0;
        int height= 0;
        int harnesses=0;
        ArrayList<ArrayList> al = new ArrayList<ArrayList>();

        BufferedReader read = new BufferedReader(new FileReader(file));
        String pattern = "";
        String hPattern = "";
        String line;
        try {
            line = read.readLine();
            width = Integer.parseInt(line.substring(3));
            line = read.readLine();
            height = Integer.parseInt(line.substring(3));
            line = read.readLine();
            harnesses = Integer.parseInt(line.substring(3));
            for(int i = 0; i< height; i++){
                al.add(new ArrayList<Integer>());
            }
            boolean harnessPattern = false;
            boolean thirdSection = false;

            // counter for arrayList al
            int a = 0;


            while ((line = read.readLine()) != null) {
                // remove \n and spaces from line
                if(!harnessPattern && !thirdSection) {
                    if(line.equals("harnessGrid:")){
                        harnessPattern = true;
                    }
                    else {
                        for (int i = 0; i < line.length(); i++) {
                            if (line.charAt(i) == ' ' || line.charAt(i) == '\n') {

                                String newLine = "";
                                for (int j = 0; j < line.length(); j++) {
                                    if (i != j) {
                                        newLine = newLine + line.charAt(j);
                                    }
                                }


                                line = newLine;
                            }
                        }
                        pattern = pattern + line;
                    }
                }
                else {
                    if (harnessPattern && !thirdSection) {
                        if(line.equals("HarnessNumbers:")) {
                            thirdSection = true;
                        }
                        else {
                            for (int i = 0; i < line.length(); i++) {
                                if (line.charAt(i) == ' ' || line.charAt(i) == '\n') {

                                    String newLine = "";
                                    for (int j = 0; j < line.length(); j++) {
                                        if (i != j) {
                                            newLine = newLine + line.charAt(j);
                                        }
                                    }


                                    line = newLine;
                                }
                            }
                            hPattern = hPattern + line;
                        }
                    }
                    else{


                        String number = "";
                        for (int i = 0; i < line.length(); i++) {
                            if(line.charAt(i)!=','){
                                number += line.charAt(i);
                                if((i+1)==line.length()){
                                    al.get(a).add(new Integer(Integer.parseInt(number)));
                                    number = "";

                                }
                            }
                            else{
                                al.get(a).add(new Integer(Integer.parseInt(number)));
                                number = "";

                            }
                        }
                        a++;
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

       new HarnessGrid(width, height, harnesses, pattern, hPattern, al);

    }

}
