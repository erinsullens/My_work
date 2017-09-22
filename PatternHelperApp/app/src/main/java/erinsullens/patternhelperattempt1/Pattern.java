package erinsullens.patternhelperattempt1;

/**
 * Created by erinsullens on 4/26/16.
 */
public class Pattern{

    public String patternName;
    public String[] patternList = new String[30];
    public int patternIterator=0;


    public Pattern(){}
    public Pattern(String name, String[] arrayOfSteps){
        this.patternName = name;
        for(int i=0; i<arrayOfSteps.length; i++){
            patternList[i] = arrayOfSteps[i];
        }
    }



    public void addPatternName(String name){
        this.patternName = name;
    }
    public void addPatternElement(String element){
        this.patternList[patternIterator] = element;
        this.patternIterator++;
    }
    public String getPatternName(){
        return this.patternName;
    }

}
