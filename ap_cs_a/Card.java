// By Collin Gros
public class Card
{
  public final int SPADES = 0, HEARTS = 1, DIAMONDS = 2, CLUBS = 3;
  public final int ACE = 1, JACK = 11, QUEEN = 12, KING = 13;
  
  int Value, Suit;
  
  public Card ()
  {
    Value = (int) Math.floor((Math.random() * 13) + 1);
    Suit = (int) Math.floor((Math.random() * 3) + 0);
  }
  
  public Card (int FinalSuit, int FinalValue)
  {
    FinalSuit = Suit;
    FinalValue = Value;
  }
  
  public String getSuit()
  {
    if (Suit == SPADES)
      return "Spades";
    else if (Suit == HEARTS)
      return "Hearts";
    else if (Suit == DIAMONDS)
      return "Diamonds";
    else if (Suit == CLUBS)
      return "Clubs";
    return "error" + Suit;
  }
  
  public String getValue()
  {
    if (Value == ACE)
      return "Ace";
    else if (Value == 2)
      return "2";
    else if (Value == 3)
      return "3";
    else if (Value == 4)
      return "4";
    else if (Value == 5)
      return "5";
    else if (Value == 6)
      return "6";
    else if (Value == 7)
      return "7";
    else if (Value == 8)
      return "8";
    else if (Value == 9)
      return "9";
    else if (Value == 10)
      return "10";
    else if (Value == JACK)
      return "Jack";
    else if (Value == QUEEN)
      return "Queen";
    else if (Value == KING)
      return "King";
    return "error" + Suit;
  }
  
  public String toString()
  {
    return getSuit() + " " + getValue();
  }
}
// Used and edited http://www.dreamincode.net/forums/topic/324162-java-creating-a-card-class-that-deals-5-random-cards/ as a source