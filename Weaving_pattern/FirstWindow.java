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

    public FirstWindow() throws FileNotFoundException {
        setSize(400, 400);

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



        JLabel widthLabel = new JLabel("Width of grid");
        p.add(widthLabel);

        JTextField widthField = new JTextField();
        p.add(widthField);
        widthField.setPreferredSize(new Dimension(50, 20));

        JLabel heightLabel = new JLabel("Width of grid");
        p.add(heightLabel);

        JTextField heightField = new JTextField();
        p.add(heightField);
        heightField.setPreferredSize(new Dimension(50, 20));

        JButton create = new JButton("Create Grid");
        p.add(create);

        JLabel warning = new JLabel("Height and width need to be an integer greater than 0");
        warning.setForeground(Color.red);
        warning.setBounds(1, 20, 2, 4);
        p.add(warning);
        warning.setVisible(false);

        String[] s = new String[savedPatterns.size()];
        for(int i = 0; i< savedPatterns.size(); i++){
            s[i] = savedPatterns.get(i);
            s[i] = s[i].substring(0,s[i].length()-4);
        }

        saved = new JComboBox<String>(s);
        saved.setPreferredSize(new Dimension(100,20));
        p.add(saved);



        JButton load = new JButton("Load Saved Pattern");
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
                if (isInteger(w) && isInteger(h)) {
                    width = Integer.parseInt(w);
                    height = Integer.parseInt(h);
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
        new Grid(width, height, harness);
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
    public void loadSaved() throws FileNotFoundException {
        String file = (String)saved.getSelectedItem();
        file = file + ".txt";
        int width = 0;
        int height= 0;

        BufferedReader read = new BufferedReader(new FileReader(file));
        String pattern = "";
        String line;
        try {
            line = read.readLine();
            width = Integer.parseInt(line.substring(3));
            line = read.readLine();
            height = Integer.parseInt(line.substring(3));

            while ((line = read.readLine()) != null) {
                // remove \n and spaces from line
                for (int i = 0; i < line.length(); i++) {
                    if (line.charAt(i) == ' ' || line.charAt(i) == '\n') {

                        String newLine = "";
                        for(int j = 0; j < line.length(); j++){
                            if(i!=j){
                                newLine = newLine + line.charAt(j);
                            }
                        }


                        line = newLine;
                    }
                }
                pattern = pattern + line;

            }
        } catch (IOException e) {
            e.printStackTrace();
        }




        int harness = 0;





        new Grid(width, height, harness, pattern);

    }

}
