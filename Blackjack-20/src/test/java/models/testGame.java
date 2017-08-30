package models;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by michaelhilton on 1/25/16.
 */
public class testGame {

    Game g = new Game();
    Player p = new Player();
    Card c = new Card(5, Suit.Hearts);

    @Test
    public void testGameCreation(){
        //Game g = new Game();
        assertNotNull(g);
    }
    @Test
    public void testDeckCount(){
       Game g = new Game();
        g.buildDeck();
       assertEquals(52,g.deck.size());
        g.deck.remove(51);
        assertEquals(51,g.deck.size());
    }


    @Test
    public void testGameBuildDeck(){
        //Game g = new Game();
        g.buildDeck();
        assertEquals(52,g.deck.size());
    }

    @Test
    public void testGameInit(){
       // Game g = new Game();
        g.buildDeck();
        g.shuffle();
        assertNotEquals(2,g.deck.get(0).getValue()); //this might fail randomly, should be improved
    }

    @Test
    public void testCustomDeal(){
        //Game g = new Game();
        g.buildDeck();
//        g.customDeal(0,3,6,9); Still not sure how this works, nor do we actually use it for anything
//        assertEquals("2Clubs",g.cols.get(0).get(0).toString());
//        assertEquals("3Clubs",g.cols.get(1).get(0).toString());
//        assertEquals("4Clubs",g.cols.get(2).get(0).toString());
//        assertEquals("5Clubs",g.cols.get(3).get(0).toString());
    }




    //This needs improvement
    @Test
    public void testHit()
    {
        g.buildDeck();
        int i = 1;
        int prevSize;
        prevSize = g.deck.size();
        g.hit(i);

        assert(g.deck.size() == (prevSize - 1));
        assert(g.cols.get(i).size() == 1);
    }


}
