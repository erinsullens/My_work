package models;


public class Player
{
    public int score;
    public int splitScore;
    public int money;
    public int betAmount;
    public int isBet;
    public int SisBet;

    public Player()
    {
        score = 0;
        money = 100;
        isBet = 0; //amount player bets
        SisBet = 0;
        betAmount = 2;
    }

    public void split(Game g){
        if((g.cols.get(1).get(0).getValue() == g.cols.get(1).get(1).getValue()) && (g.cols.get(1).size() == 2)) {//if card 1 value == card 2 and you only have 2 cards
            g.move(1, 2); //moves one of the cards over to the new stack
            g.SwinState = "p";
            bet(2);
            this.score = g.getColScore(1);
            this.splitScore = g.getColScore(2);
        }
    }

    public void doubleDown(int i, Game g){
        bet(i);
        g.hit(i); //TODO ACTUALLY IMPLEMENT THIS I THINK IT"S WRONG ALSO CHECK TO MAKE SURE YOU CAN DO IT
        stay(g);
    }

    public void bet(int i)
    {
        if (money >= betAmount)
        {
            if(i == 1) {
              //  money = money - betAmount;
                isBet = isBet + betAmount;
            }
            if(i == 2)
            {
               // money = money - betAmount;
                SisBet = SisBet + betAmount;
            }
        }
        else
        {
            System.out.println("Not enough money");
        }
    }

    public void stay(Game g) {
        g.dealersTurn = "t";
        int dealScore = g.getColScore(0);
        while(dealScore <= 16) { //dealer keeps hitting
            g.hit(0);
            dealScore = g.getColScore(0);
        }

        if(g.p.score > 21){
            g.winState="l";
            g.p.money -= g.p.isBet;
        }
        else {

            if (dealScore > 21) {
                g.winState = "w";
                g.p.money += g.p.isBet;
            }
            if (dealScore < g.p.score && g.p.score <= 21) {
                g.winState = "w";
                g.p.money += g.p.isBet;
            }
            if (dealScore > g.p.score && dealScore <= 21) {
                g.winState = "l";
                g.p.money -= g.p.isBet;
            }
            if (dealScore == g.p.score) {
                g.winState = "t";
                g.p.money += g.p.isBet;
            }
            if (g.SwinState == "p") {
                if (dealScore > 21) {
                    g.SwinState = "w";
                    g.p.money += g.p.SisBet;
                }
                if (dealScore < g.p.splitScore) {
                    g.SwinState = "w";
                    g.p.money += g.p.SisBet;
                }
                if (dealScore > g.p.splitScore && dealScore <= 21) {
                    g.SwinState = "l";
                    g.p.money -= g.p.SisBet;
                }
                if (dealScore == g.p.splitScore) {
                    g.SwinState = "t";
                }
            }
        }
        return;
        //TODO NEEDS LEYGIT GAME SCORING AND ENDING
        }
    
}
