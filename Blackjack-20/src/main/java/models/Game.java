package models;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;

/*
 * Created by michaelhilton on 1/25/16.
 */
public class Game {

    public java.util.List<Card> deck = new ArrayList<>();
    public java.util.List<java.util.List<Card>> cols = new ArrayList<>();
    public String dealersTurn;
    public Player p;
    public int dealerScore;
    public String busted = "You busted! Please hit the New Hand button to start a new hand!";
    public String win = "You won! Please hit New Hand to start a new hand!";
    public String tied = "You tied with the dealer! Please hit the New Hand button to start a new hand!";
    public String winState = "p"; //p for still playing, w for win, l for loss, t for tie, b for bust
    public String SwinState = "d"; //d for dead/not active, p for playing, w for win, l for loss, t for tie, b for bust for the split col
    public String blank="";
    public String youLost = "You lost! Please hit the New Hand button to start a new hand!";
    public String split = "On your split hand, ";

    public Game(){ //This needs to be changed first really. 3 columns, 0 for dealer, 1 for hand 1, 2 for hand 2
        cols.add(new ArrayList<Card>()); //0
        cols.add(new ArrayList<Card>()); //1
        cols.add(new ArrayList<Card>()); //2
        p = new Player();
    }
   public int getColScore(int columnNumber)
    {
        int total = 0;
        int ace = 0;
        for(int i = 0; i < this.cols.get(columnNumber).size(); i++) {
            if (this.cols.get(columnNumber).get(i).getValue() == 14) {
                ace ++;
                total += 11;
            } else {
                if (this.cols.get(columnNumber).get(i).getValue() == 11 || this.cols.get(columnNumber).get(i).getValue() == 12 || this.cols.get(columnNumber).get(i).getValue() == 13) {
                    total += 10;
                } else {
                    total += this.cols.get(columnNumber).get(i).getValue();
                }
            }
            while(total > 21 && ace>=1){
                total -= 11;
                total++;
                ace--;
            }
        }
        return total;
    }

    public void buildDeck() {
        for(int i = 2; i < 15; i++){
            deck.add(new Card(i,Suit.Clubs));
            deck.add(new Card(i,Suit.Hearts));
            deck.add(new Card(i,Suit.Diamonds));
            deck.add(new Card(i,Suit.Spades));
        }
    }

    public void newGame(){
        this.dealersTurn = "f";
        this.cols.get(0).clear();
        this.cols.get(1).clear();
        this.cols.get(2).clear();
        this.deck.clear();
        this.p.score= 0;
        this.dealerScore = 0;
        this.buildDeck();
        this.shuffle();
        this.dealHands();
        this.winState = "p";
        this.SwinState = "d";
        this.p.splitScore = 0;
        this.p.isBet = 0;
        this.p.SisBet = 0;
        this.p.bet(1);
    }

    public void shuffle() {
        long seed = System.nanoTime();
        Collections.shuffle(deck, new Random(seed));
    }
    public void hit(int i){ //i is 0 for dealer, 1 for hand 1, 2 for hand 2 if split
        if (i == 2 && this.SwinState.equals("d"))
            return;
        cols.get(i).add(deck.get(deck.size()-1));
        deck.remove(deck.size()-1);
        if(i == 0)
            this.dealerScore = this.getColScore(0);
        if(i == 1)
            this.p.score = this.getColScore(i);
        if(i == 2)
            this.p.splitScore = this.getColScore(i);

        if((this.p.score > 21) && !(this.winState.equals("b"))){
            this.p.money-= this.p.isBet;
            this.winState = "b";
        }
        if((this.p.splitScore > 21) && !(this.SwinState.equals("b"))){
            this.p.money-= this.p.SisBet;
            this.SwinState = "b";
        }

    }

    public void dealHands() {
        hit(0);
        hit(0);
        hit(1);
        hit(1);
     }

    /* function not needed
    public void customDeal(int c1, int c2, int c3, int c4) {
        cols.get(0).add(deck.get(c1));
        deck.remove(c1);
        cols.get(1).add(deck.get(c2));
        deck.remove(c2);
        cols.get(2).add(deck.get(c3));
        deck.remove(c3);
        cols.get(3).add(deck.get(c4));
        deck.remove(c4);
    }
    */
  /*
    public void remove(int columnNumber) {
        if(colHasCards(columnNumber)) {
            Card c = getTopCard(columnNumber);
            boolean removeCard = false;
            for (int i = 0; i < 4; i++) {
                if (i != columnNumber) {
                    if (colHasCards(i)) {
                        Card compare = getTopCard(i);
                        if (compare.getSuit() == c.getSuit()) {
                            if (compare.getValue() > c.getValue()) {
                                removeCard = true;
                            }
                        }
                    }
                }
            }
            if (removeCard) {
                this.cols.get(columnNumber).remove(this.cols.get(columnNumber).size() - 1);
            }
        }
    }
*/
    private boolean colHasCards(int colNumber) {
        return this.cols.get(colNumber).size() > 0;
    }

    private Card getTopCard(int columnNumber) {
        return this.cols.get(columnNumber).get(this.cols.get(columnNumber).size()-1);
    }
    public int deckSize(){
        return deck.size();
    }

    public void move(int colFrom, int colTo) {
        if (!colHasCards(colTo))
        {
            Card cardToMove = getTopCard(colFrom);
            this.removeCardFromCol(colFrom);
            this.addCardToCol(colTo, cardToMove);
        }
        else
        {
            System.out.println("Don\'t you dare to move that card");
        }
    }

    public void addCardToCol(int colTo, Card cardToMove) {
        cols.get(colTo).add(cardToMove);
    }

    private void removeCardFromCol(int colFrom) {
        this.cols.get(colFrom).remove(this.cols.get(colFrom).size()-1);

    }
}
