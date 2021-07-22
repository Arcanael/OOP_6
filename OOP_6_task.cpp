#include <iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;


////////////////////////////////////////////////////////////////////////
// 1 задание
////////////////////////////////////////////////////////////////////////




bool inputINT(string input)
{
    for (size_t i = 0; i < input.size(); i++)
    {
        if (!isdigit(input[i]))
        {
            return false;
        }
    }
    return true;
}


//int main()
//{
//    
//    int int_num;
//    string s;
//    while(true)
//    {
//        
//        cout << "Введите целое число" << endl<<endl;
//        getline(cin, s);
//        if (inputINT(s)) { break; }
//        
//    }
//    cout << "\nВы ввели!\n"<<s<<endl;
//}





////////////////////////////////////////////////////////////////////////
// 2 задание
////////////////////////////////////////////////////////////////////////






ostream& endll(ostream& stream)
{
    
    stream << endl << endl;
    stream.clear();
    return stream;
}
int main()
{
    cout << 1 << endll << 2;
    return 0;
}





////////////////////////////////////////////////////////////////////////
// 3 задание
////////////////////////////////////////////////////////////////////////







class Card
{
public:
    enum suit
    {
        CLUBS,
        SPADES,
        HEARTS,
        DIMONDS
    };
    enum rank
    {
        ACE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 10,
        QUEEN = 10,
        KING = 10,

    };

    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    void Flip();
    int GetValue() const;

    rank getRank()const { return m_Rank; } 
    suit getSuit()const { return m_Suit; }
    bool getIFU()const { return m_IsFaceUp; }
    
    friend ostream& operator<<(ostream& os, const Card& aCard);

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) {}

int Card::GetValue()const
{
    int value = 0;
    if (m_IsFaceUp)
    {
        value = m_Rank;
        if (value > 10)
        {
            value = 10;
        }
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !(m_IsFaceUp);
}


class Hand
{
public:
    Hand();
    
    virtual ~Hand();

    
    void Add(Card* pCard);

    
    void Clear();

    
    int GetTotal() const;

protected:
    vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}

Hand::~Hand()
{
    Clear();
}

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}


void Hand::Clear()
{
   
    vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete* iter;
        *iter = 0;
    }
   
    m_Cards.clear();
}


int Hand::GetTotal() const
{
    
    if (m_Cards.empty())
    {
        return 0;
    }

   
    if (m_Cards[0]->GetValue() == 0)
    {
        return 0;
    }

    int total = 0;
    vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }

    
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if ((*iter)->GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }

    // если рука держит туз и сумма довольно маленькая, туз дает 11 очков
    if (containsAce && total <= 11)
    {
        total += 10;
    }

    return total;
}





// абстрактный класс
class GenericPlayer : public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer);

public:
    GenericPlayer(const string& name = "");

    virtual ~GenericPlayer();
    
    virtual bool IsHitting() const = 0;
    
    bool IsBusted() const;

    void Bust() const;

protected:
    string m_Name;
};

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

class Player : public GenericPlayer
{
public:
    Player(const string& name = "");

    virtual ~Player();

    
    virtual bool IsHitting() const;

    
    void Win() const;

   
    void Lose() const;

   
    void Push() const;
};


bool Player::IsHitting() const
{
    cout << m_Name << ", do you want a hit? (Y/N): ";
    char response;
    cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::Win() const
{
    cout << m_Name << " wins.\n";
}

void Player::Lose() const
{
    cout << m_Name << " loses.\n";
}

void Player::Push() const
{
    cout << m_Name << " pushes.\n";
}



////////////////////////////////////////////////////////////////////////
// 4 задание
////////////////////////////////////////////////////////////////////////





class House : public GenericPlayer
{
public:
    House(const string& name = "House");

    virtual ~House();

   
    virtual bool IsHitting() const;

    
    void FlipFirstCard();
};

bool House::IsHitting() const
{
    return (GetTotal() <= 16);
}

void House::FlipFirstCard()
{
    if (!(m_Cards.empty()))
    {
        m_Cards[0]->Flip();
    }
    else
    {
        cout << "No card to flip!\n";
    }
}



////////////////////////////////////////////////////////////////////////
// 5 задание
////////////////////////////////////////////////////////////////////////





ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "c", "d", "h", "s" };

    if (aCard.getIFU())
    {
        os << RANKS[aCard.getRank()] << SUITS[aCard.getSuit()];
    }
    else
    {
        os << "XX";
    }

    return os;
}


ostream& operator<<(ostream& os, const GenericPlayer& aGenericPlayer)
{
    os << aGenericPlayer.m_Name << ":\t";

    vector<Card*>::const_iterator pCard;
    if (!aGenericPlayer.m_Cards.empty())
    {
        for (pCard = aGenericPlayer.m_Cards.begin();
            pCard != aGenericPlayer.m_Cards.end();
            ++pCard)
        {
            os << *(*pCard) << "\t";
        }


        if (aGenericPlayer.GetTotal() != 0)
        {
            cout << "(" << aGenericPlayer.GetTotal() << ")";
        }
    }
    else
    {
        os << "<empty>";
    }

    return os;
}

This text is added to the end of the file
