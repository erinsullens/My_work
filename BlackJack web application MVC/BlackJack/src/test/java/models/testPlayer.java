package models;

import org.junit.Test;

/**
 * Created by lehaz_000 on 09.03.2016.
 */
public class testPlayer {

    Game g = new Game();
    Player p = new Player();
    Card testCard1 = new Card(10, Suit.Clubs);
    Card testCard2 = new Card(9, Suit.Hearts);

    @Test
    public void testBet()
    {
        int testBetAmount;
        p.money = 10;
        p.isBet = 0;
        p.betAmount = 2;

        //If player has enough money
        //testBetAmount = 2;
        p.bet(1);
        assert(p.isBet == 2);

        //If player doesn't have enough money
        p.money = 1;
        p.bet(1);
        assert(p.isBet == 2);
    }

    @Test
    public void testStay() {
        Card king = new Card(10, Suit.Clubs);
        Card ace = new Card(11, Suit.Diamonds);
        Card two = new Card(2, Suit.Hearts);

        g.addCardToCol(0,king);
        g.addCardToCol(0,ace);
        g.p.score = 3;
        p.stay(g);
        assert(g.winState == "l");

        g.p.score = 20;
        p.stay(g);
        assert(g.winState == "t");

        g.p.score = 21;
        p.stay(g);
        assert(g.winState == "w");

        g.p.score = 25;
        p.stay(g);
        assert(g.winState == "l");
        g.p.score = 10;

        g.SwinState = "p";
        g.p.splitScore = 15;
        p.stay(g);
        assert(g.SwinState == "l");

        g.SwinState = "p";
        g.p.splitScore = 20;
        p.stay(g);
        assert(g.SwinState == "t");

        g.SwinState = "p";
        g.p.splitScore = 21;
        p.stay(g);
        assert(g.SwinState == "w");
    }

    @Test
    public void testSplit(){
        g.addCardToCol(1,testCard1);
        g.addCardToCol(1,testCard1);
        p.split(g);
        assert(g.cols.get(2).size() == 1);

        g.cols.get(1).clear();
        g.cols.get(2).clear();
        g.addCardToCol(1,testCard1);
        g.addCardToCol(1,testCard2);
        p.split(g);
        assert(g.cols.get(2).size() == 0); //should be empty as that split is illegal
    }

    @Test
    public void testDoubleDown()
    {
        g.newGame();

        int i = 1;
        int testBetAmount = 2;
        int prevSize, prevBet;
        prevSize = g.deck.size();
        prevBet = p.isBet;
        p.doubleDown(i,g);


        assert(p.isBet == (prevBet + testBetAmount));

    }
}
