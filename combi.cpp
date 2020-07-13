#include <iostream>
using namespace std;
#include <SFML/Window.hpp>
using namespace sf;
#include <SFML/System.hpp>
using namespace sf;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <SFML/Audio.hpp>
using namespace sf;
#include <sstream>
#include <string>
#include <string.h>
#include <fstream>

//////////////////////////////////////////////////////global variable////////////////////////////////////////////////////////
string words[30];
string str_highscore[11];
int int_highscore[11];
int score=0;
int rank=0;
char input[1000];
char output[1000];

//////////////////////////////////////////////////////functions prototype////////////////////////////////////////////////////
int get_score();
int str_to_int();
int arrange_score();
int write_score();
int fill_words_bank();
string intstr(int z);
int front_window();
string input_string();
int game_window();
int highscore_window();
int score_rank(int);
int display_highscore_window();
//void credit_window();

///////////////////////////////////////////////////////functions////////////////////////////////////////////////////////////
int get_score()
{
	int i=0;
	ifstream high;
	high.open("data/text/highscore.txt");
	for (i=0; i<10; i++)
{
	high >> str_highscore[i];
}
return 0;
}

int str_to_int()
{
	int i;
	for (i=0; i<11; i++)
{
	int_highscore[i] = atoi (str_highscore[i].c_str());
}
return 0;
}

int arrange_score()
{
	int i, j;
	for (i=0;i<=9;i++)
	{
		for (j=i+1;j<=10;j++)
		{
			if (int_highscore[j]>int_highscore[i])
			{
				int temp;
				temp=int_highscore[i];
				int_highscore[i]=int_highscore[j];
				int_highscore[j]=temp;
			}

		}
	}
	return 0;
}

int write_score()
{
int i=0;
	ofstream high;
	high.open("data/text/highscore.txt");
	for (i=0; i<11; i++)
{
	high << int_highscore[i] << endl;
}
high.close();
return 0;
}

int fill_words_bank()
{
	int i;
	ifstream avi;
	avi.open("data/text/words.txt");
	for (i=0;i<30;i++)
	{
		avi >> words[i];
	}
	avi.close();
	return 0;
}

string intstr(int z)
{
stringstream ss;
ss << z;
string str = ss.str();
return ss.str();
}

int score_rank(int z)
{

	int i;
	for (i=0;i<11;i++)
	{
		rank++;
	if (int_highscore[i]==z)
		{
			break;
		}
	}
	return 0;
}

string input_string()
{
	ifstream avi;
	avi.open("data/text/words.txt");
	stringstream buffer;
	buffer << avi.rdbuf();
	avi.close();
	return buffer.str();
}

////////////////////////////////////////////////////////Windows////////////////////////////////////////////////////////////////

int front_window()
{
	int set=1;

RenderWindow window(VideoMode(1280, 720), "Menu", Style::Titlebar | Style::Close);


Font font;
font.loadFromFile("data/font/arial.ttf");

Text top("TYPING MASTER", font, 60);
top.setStyle(Text::Bold);
top.setColor(Color::White);
top.setPosition(400,50);

Texture texture;
texture.loadFromFile("data/png/1.png");
if(!texture.loadFromFile("data/png/1.png"))
{
	cerr << "Image not found" << endl;
}
Sprite sprite;
sprite.setTexture(texture);

SoundBuffer move_buffer;
move_buffer.loadFromFile("data/sound/move.wav");
Sound move_sound;
move_sound.setBuffer(move_buffer);

SoundBuffer select_buffer;
select_buffer.loadFromFile("data/sound/select.wav");
Sound select_sound;
select_sound.setBuffer(select_buffer);

Texture green;
green.loadFromFile("data/png/green.png");
Texture grey;
grey.loadFromFile("data/png/grey.png");

Sprite button1;
button1.setTexture(grey);
button1.setPosition(500,300);

Sprite button2;
button2.setTexture(grey);
button2.setPosition(500,375);

Sprite button3;
button3.setTexture(grey);
button3.setPosition(500,450);

Sprite button4;
button4.setTexture(grey);
button4.setPosition(500,525);

Text text_button1("Start",font,20);
text_button1.setColor(Color::Black);
text_button1.setStyle(Text::Bold);
text_button1.setPosition(620, 309);

Text text_button2("High Score",font,20);
text_button2.setColor(Color::Black);
text_button2.setStyle(Text::Bold);
text_button2.setPosition(590, 384);

Text text_button3("Credit",font,20);
text_button3.setColor(Color::Black);
text_button3.setStyle(Text::Bold);
text_button3.setPosition(615, 458);

Text text_button4("Exit",font,20);
text_button4.setColor(Color::Black);
text_button4.setStyle(Text::Bold);
text_button4.setPosition(625, 534);


Event event;
	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{

		while (window.pollEvent(event))

		{
		switch (event.type)
			{
		case Event::Closed:
		window.close();
		break;

		case Event::TextEntered:
        if	(event.text.unicode==13)
	{
	    select_sound.play();
		if (set==1)
        {
			window.close();
            game_window();
            return 0;
        }
        if (set==2)
        {
			window.close();
            highscore_window();
            return 0;
			//break;
        }
        if (set==3)
        {
            cout << "Credit" << endl;
            /*window.close();
            credit_window();
			return 0;;*/
        }
        if (set==4)
        {
            window.close();
            return 0;
        }

    }
			}

		if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            move_sound.play();
        set--;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            move_sound.play();
        set++;
        }
    }

	if (set<1)
    {
        set=4;
    }
    if (set>4)
    {
        set=1;
    }
    if (set==1)
    {
        button1.setTexture(green);
        button2.setTexture(grey);
        button4.setTexture(grey);
    }
    if (set==2)
    {
        button2.setTexture(green);
        button1.setTexture(grey);
        button3.setTexture(grey);
    }
    if (set==3)
    {
        button3.setTexture(green);
        button2.setTexture(grey);
        button4.setTexture(grey);
    }
    if (set==4)
    {
        button4.setTexture(green);
        button1.setTexture(grey);
        button3.setTexture(grey);
    }

window.clear();
window.draw(sprite);
window.draw(button1);
window.draw(button2);
window.draw(button3);
window.draw(button4);
window.draw(text_button1);
window.draw(text_button2);
window.draw(text_button3);
window.draw(text_button4);
window.draw(top);
window.display();
}
return 0;
}


int game_window()
{
	string s="";
	//int type_time=0;
	int sec=0;
	int sec_ten=0;
	int minute=0;
	int minute_ten=0;
	int hour=0;
	float easy=0.2;
	float medium=0.4;
	float hard=0.7;
	int secs;
	int score=0;
	int lives=10;
	int level_update=0;
	int for_in=0;
	int for_out=0;
	strcpy(output,input_string().c_str());
	int man_position=1200;
	int wslide_position=750;
	int temp;

////////////////////////////////////////////////////////////level selection... Default is easy/////////////////////////////////////
	float level = easy;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	int i=0;
	int j=0;
	int xtra_life=0;
	fill_words_bank();
	int num_word=0;


RenderWindow window(VideoMode(1280, 720), "Game", Style::Titlebar | Style::Close);
Clock game_clock;
Clock word_count_clock;
Clock word_slide_clock;


Texture texture;
texture.loadFromFile("data/png/2.png");
if(!texture.loadFromFile("data/png/2.png"))
{
	cerr << "Image not found" << endl;
}
Sprite sprite;
sprite.setTexture(texture);



///////////////////////////////////////////////////////////keyboard texture/////////////////////////////////////////////////////////
Texture key;
key.loadFromFile("data/png/key.png", IntRect(2, 2, 1274, 282));

Sprite sprite_keyboard;
sprite_keyboard.setPosition(0,400);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////Sounds///////////////////////////////////////////////////////
SoundBuffer type_buffer;
type_buffer.loadFromFile("data/sound/type.wav");
Sound type_sound;
type_sound.setBuffer(type_buffer);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Font font;
font.loadFromFile("data/font/arial.ttf");

Text text_score("Score:",font,20);
text_score.setColor(Color::White);
text_score.setStyle(Text::Bold);
text_score.setPosition(1170, 5);

Text display_score("",font,20);
display_score.setColor(Color::White);
display_score.setStyle(Text::Bold);
display_score.setPosition(1235, 6);

Text text_lives("Lives:",font,20);
text_lives.setColor(Color::White);
text_lives.setStyle(Text::Bold);
text_lives.setPosition(825, 5);

Text display_lives("",font,20);
display_lives.setColor(Color::White);
display_lives.setStyle(Text::Bold);
display_lives.setPosition(885, 6);

Text text_time("Time elapsed: ",font,20);
text_time.setColor(Color::White);
text_time.setStyle(Text::Bold);
text_time.setPosition(5, 3);

Text text_speed("Speed:      W.P.M ", font, 20);
text_speed.setColor(Color::White);
text_speed.setStyle(Text::Bold);
text_speed.setPosition(330, 4);

Text text_user_input("",font,20);
text_user_input.setColor(Color::White);
text_user_input.setStyle(Text::Bold);
text_user_input.setPosition(50, 348);

Text display_sec_ten("",font,20);
display_sec_ten.setColor(Color::White);
display_sec_ten.setStyle(Text::Bold);
display_sec_ten.setPosition(182, 5);

Text display_sec("",font,20);
display_sec.setColor(Color::White);
display_sec.setStyle(Text::Bold);
display_sec.setPosition(172, 5);

Text text_seperator(":",font,20);
text_seperator.setColor(Color::White);
text_seperator.setStyle(Text::Bold);
text_seperator.setPosition(166, 3);

Text display_min_ten("",font,20);
display_min_ten.setColor(Color::White);
display_min_ten.setStyle(Text::Bold);
display_min_ten.setPosition(155, 5);

Text display_min("",font,20);
display_min.setColor(Color::White);
display_min.setStyle(Text::Bold);
display_min.setPosition(145, 5);

Text display_wordspeed("",font,20);
display_wordspeed.setColor(Color::White);
display_wordspeed.setStyle(Text::Bold);
display_wordspeed.setPosition(400, 5);

Text current_word("",font,20);
current_word.setPosition(620,50);


//For the type word line
RectangleShape typeline(Vector2f(1280, 30));
typeline.setPosition(0,348);
typeline.setFillColor(Color(0,0,0));

//for slide line
RectangleShape slideline(Vector2f(1280, 50));
slideline.setPosition(0,280);
slideline.setFillColor(Color(0,0,0));

RectangleShape shark(Vector2f(80,50));
shark.setPosition(0,200);
shark.setFillColor(Color::Blue);

RectangleShape man(Vector2f(80,50));
man.setFillColor(Color::Blue);

Text string_slide(input_string(), font, 54);

Text input_string("", font, 24);
input_string.setPosition(5,400);





	Event event;


	while (window.isOpen())
	{


		while (window.pollEvent(event))

		{
		switch (event.type)
			{
		case Event::Closed:
		front_window();
		window.close();
		return 0;
		
	case Event::TextEntered:
	if	(event.text.unicode==65)
	{
		string ss="A";
		s=s+ss;
		type_sound.play();
		input[for_in]='A';
		key.loadFromFile("data/png/3_2.png", IntRect(2, 2, 1274, 282));

}
	if	(event.text.unicode==66)
	{
		string ss="B";
		s=s+ss;
		type_sound.play();
		input[for_in]='B';
		key.loadFromFile("data/png/4_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==67)
	{
		string ss="C";
		s=s+ss;
		type_sound.play();
		input[for_in]='C';
		key.loadFromFile("data/png/4_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==68)
	{
		string ss="D";
		s=s+ss;
		type_sound.play();
		input[for_in]='D';
		key.loadFromFile("data/png/3_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==69)
	{
		string ss="E";
		s=s+ss;
		input[for_in]='E';
		type_sound.play();
		key.loadFromFile("data/png/2_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==70)
	{
		string ss="F";
		s=s+ss;
		type_sound.play();
		input[for_in]='F';
		key.loadFromFile("data/png/3_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==71)
	{
		string ss="G";
		s=s+ss;
		type_sound.play();
		input[for_in]='G';
		key.loadFromFile("data/png/3_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==72)
	{
		string ss="H";
		s=s+ss;
		type_sound.play();
		input[for_in]='H';
		key.loadFromFile("data/png/3_7.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==73)
	{
		string ss="I";
		s=s+ss;
		type_sound.play();
		input[for_in]='I';
		key.loadFromFile("data/png/2_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==74)
	{
		string ss="J";
		s=s+ss;
		type_sound.play();
		input[for_in]='J';
		key.loadFromFile("data/png/3_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==75)
	{
		string ss="K";
		s=s+ss;
		type_sound.play();
		input[for_in]='K';
		key.loadFromFile("data/png/3_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==76)
	{
		string ss="L";
		s=s+ss;
		type_sound.play();
		input[for_in]='L';
		key.loadFromFile("data/png/3_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==77)
	{
		string ss="M";
		s=s+ss;
		type_sound.play();
		input[for_in]='M';
		key.loadFromFile("data/png/4_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==78)
	{
		string ss="N";
		s=s+ss;
		type_sound.play();
		input[for_in]='N';
		key.loadFromFile("data/png/4_7.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==79)
	{
		string ss="O";
		s=s+ss;
		type_sound.play();
		input[for_in]='O';
		key.loadFromFile("data/png/2_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==80)
	{
		string ss="P";
		s=s+ss;
		type_sound.play();
		input[for_in]='P';
		key.loadFromFile("data/png/2_11.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==81)
	{
		string ss="Q";
		s=s+ss;
		type_sound.play();
		input[for_in]='Q';
		key.loadFromFile("data/png/2_2.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==82)
	{
		string ss="R";
		s=s+ss;
		type_sound.play();
		input[for_in]='R';
		key.loadFromFile("data/png/2_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==83)
	{
		string ss="S";
		s=s+ss;
		type_sound.play();
		input[for_in]='S';
		key.loadFromFile("data/png/3_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==84)
	{
		string ss="T";
		s=s+ss;
		type_sound.play();
		input[for_in]='T';
		key.loadFromFile("data/png/2_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==85)
	{
		string ss="U";
		s=s+ss;
		type_sound.play();
		input[for_in]='U';
		key.loadFromFile("data/png/2_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==86)
	{
		string ss="V";
		s=s+ss;
		type_sound.play();
		input[for_in]='V';
		key.loadFromFile("data/png/4_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==87)
	{
		string ss="W";
		s=s+ss;
		type_sound.play();
		input[for_in]='W';
		key.loadFromFile("data/png/2_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==88)
	{
		string ss="X";
		s=s+ss;
		type_sound.play();
		input[for_in]='X';
		key.loadFromFile("data/png/4_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==89)
	{
		string ss="Y";
		s=s+ss;
		type_sound.play();
		input[for_in]='Y';
		key.loadFromFile("data/png/2_7.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==90)
	{
		string ss="Z";
		s=s+ss;
		type_sound.play();
		input[for_in]='Z';
		key.loadFromFile("data/png/4_2.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==97)
	{
		string ss="a";
		s=s+ss;
		type_sound.play();
		input[for_in]='a';
		key.loadFromFile("data/png/3_2.png", IntRect(2, 2, 1274, 282));;

	}
	if	(event.text.unicode==98)
	{
		string ss="b";
		s=s+ss;
		type_sound.play();
		input[for_in]='b';
		key.loadFromFile("data/png/4_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==99)
	{
		string ss="c";
		s=s+ss;
		type_sound.play();
		input[for_in]='c';
		key.loadFromFile("data/png/4_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==100)
	{
		string ss="d";
		s=s+ss;
		type_sound.play();
		input[for_in]='d';
		key.loadFromFile("data/png/3_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==101)
	{
		string ss="e";
		s=s+ss;
		type_sound.play();
		input[for_in]='e';
		key.loadFromFile("data/png/2_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==102)
	{
		string ss="f";
		s=s+ss;
		type_sound.play();
		input[for_in]='f';
		key.loadFromFile("data/png/3_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==103)
	{
		string ss="g";
		s=s+ss;
		type_sound.play();
		input[for_in]='g';
		key.loadFromFile("data/png/3_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==104)
	{
		string ss="h";
		s=s+ss;
		type_sound.play();
		input[for_in]='h';
		key.loadFromFile("data/png/3_7.png", IntRect(2, 2, 1274, 282));;
	}
	if	(event.text.unicode==105)
	{
		string ss="i";
		s=s+ss;
		type_sound.play();
		input[for_in]='i';
		key.loadFromFile("data/png/2_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==106)
	{
		string ss="j";
		s=s+ss;
		type_sound.play();
		input[for_in]='j';
		key.loadFromFile("data/png/3_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==107)
	{
		string ss="k";
		s=s+ss;
		type_sound.play();
		input[for_in]='k';
		key.loadFromFile("data/png/3_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==108)
	{
		string ss="l";
		s=s+ss;
		type_sound.play();
		input[for_in]='l';
		key.loadFromFile("data/png/3_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==109)
	{
		string ss="m";
		s=s+ss;
		type_sound.play();
		input[for_in]='m';
		key.loadFromFile("data/png/4_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==110)

	{
		string ss="n";
		s=s+ss;
		type_sound.play();
		input[for_in]='n';
		key.loadFromFile("data/png/4_7.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==111)
	{
		string ss="o";
		s=s+ss;
		type_sound.play();
		input[for_in]='o';
		key.loadFromFile("data/png/2_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==112)
	{
		string ss="p";
		s=s+ss;
		type_sound.play();
		input[for_in]='p';
		key.loadFromFile("data/png/2_11.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==113)
	{
		string ss="q";
		s=s+ss;
		type_sound.play();
		input[for_in]='q';
		key.loadFromFile("data/png/2_2.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==114)
	{
		string ss="r";
		s=s+ss;
		type_sound.play();
		input[for_in]='r';
		key.loadFromFile("data/png/2_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==115)
	{
		string ss="s";
		s=s+ss;
		type_sound.play();
		input[for_in]='s';
		key.loadFromFile("data/png/3_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==116)
	{
		string ss="t";
		s=s+ss;
		type_sound.play();
		input[for_in]='t';
		key.loadFromFile("data/png/2_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==117)
	{
		string ss="u";
		s=s+ss;
		type_sound.play();
		input[for_in]='u';
		key.loadFromFile("data/png/2_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==118)
	{
		string ss="v";
		s=s+ss;
		type_sound.play();
		input[for_in]='v';
		key.loadFromFile("data/png/4_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==119)
	{
		string ss="w";
		s=s+ss;
		type_sound.play();
		input[for_in]='w';
		key.loadFromFile("data/png/2_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==120)
	{
		string ss="x";
		s=s+ss;
		type_sound.play();
		input[for_in]='x';
		key.loadFromFile("data/png/4_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==121)
	{
		string ss="y";
		s=s+ss;
		type_sound.play();
		input[for_in]='y';
		key.loadFromFile("data/png/2_7.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==122)
	{
		string ss="z";
		s=s+ss;
		type_sound.play();
		input[for_in]='z';
		key.loadFromFile("data/png/4_2.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==96)
	{
		string ss="`";
		s=s+ss;
		type_sound.play();
		input[for_in]='`';
		key.loadFromFile("data/png/1_1.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==126)
	{
		string ss="~";
		s=s+ss;
		type_sound.play();
		input[for_in]='~';
		key.loadFromFile("data/png/1_1.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==49)
	{
		string ss="1";
		s=s+ss;
		type_sound.play();
		input[for_in]='1';
		key.loadFromFile("data/png/1_2.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==33)
	{
		string ss="!";
		s=s+ss;
		type_sound.play();
		input[for_in]='!';
		key.loadFromFile("data/png/1_2.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==50)
	{
		string ss="2";
		s=s+ss;
		type_sound.play();
		input[for_in]='2';
		key.loadFromFile("data/png/1_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==64)
	{
		string ss="@";
		s=s+ss;
		type_sound.play();
		input[for_in]='@';
		key.loadFromFile("data/png/1_3.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==51)
	{
		string ss="3";
		s=s+ss;
		type_sound.play();
		input[for_in]='3';
		key.loadFromFile("data/png/1_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==35)
	{
		string ss="#";
		s=s+ss;
		type_sound.play();
		input[for_in]='#';
	key.loadFromFile("data/png/1_4.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==52)
	{
		string ss="4";
		s=s+ss;
		type_sound.play();
		input[for_in]='4';
		key.loadFromFile("data/png/1_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==36)
	{
		string ss="$";
		s=s+ss;
		type_sound.play();
		input[for_in]='$';
		key.loadFromFile("data/png/1_5.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==53)
	{
		string ss="5";
		s=s+ss;
		type_sound.play();
		input[for_in]='5';
		key.loadFromFile("data/png/1_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==37)
	{
		string ss="%";
		s=s+ss;
		type_sound.play();
		input[for_in]='%';
		key.loadFromFile("data/png/1_6.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==54)
	{
		string ss="6";
		s=s+ss;
		type_sound.play();
		input[for_in]='6';
		key.loadFromFile("data/png/1_7.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==94)
	{
		string ss="^";
		s=s+ss;
		type_sound.play();
		input[for_in]='^';
		key.loadFromFile("data/png/1_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==55)
	{
		string ss="7";
		s=s+ss;
		type_sound.play();
		input[for_in]='7';
		key.loadFromFile("data/png/1_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==38)
	{
		string ss="&";
		s=s+ss;
		type_sound.play();
		input[for_in]='&';
		key.loadFromFile("data/png/1_8.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==56)
	{
		string ss="8";
		s=s+ss;
		type_sound.play();
		input[for_in]='8';
		key.loadFromFile("data/png/1_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==42)
	{
		string ss="*";
		s=s+ss;
		type_sound.play();
		input[for_in]='*';
		key.loadFromFile("data/png/1_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==57)
	{
		string ss="9";
		s=s+ss;
		type_sound.play();
		input[for_in]='9';
		key.loadFromFile("data/png/1_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==40)
	{
		string ss="(";
		s=s+ss;
		type_sound.play();
		input[for_in]='(';
		key.loadFromFile("data/png/1_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==48)
	{
		string ss="0";
		s=s+ss;
		type_sound.play();
		input[for_in]='0';
		key.loadFromFile("data/png/1_11.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==41)
	{
		string ss=")";
		s=s+ss;
		type_sound.play();
		input[for_in]=')';
		key.loadFromFile("data/png/1_11.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==45)
	{
		string ss="-";
		s=s+ss;
		type_sound.play();
		input[for_in]='-';
		key.loadFromFile("data/png/1_12.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==95)
	{
		string ss="_";
		s=s+ss;
		type_sound.play();
		input[for_in]='_';
		key.loadFromFile("data/png/1_12.png", IntRect(2, 2, 1274, 282));;
	}
	if	(event.text.unicode==61)
	{
		string ss="=";
		s=s+ss;
		type_sound.play();
		input[for_in]='=';
		key.loadFromFile("data/png/1_13.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==43)
	{
		string ss="+";
		s=s+ss;
		type_sound.play();
		input[for_in]='+';
		key.loadFromFile("data/png/1_13.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==91)
	{
		string ss="[";
		s=s+ss;
		type_sound.play();
		input[for_in]='[';
	key.loadFromFile("data/png/2_12.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==123)
	{
		string ss="{";
		s=s+ss;
		type_sound.play();
		input[for_in]='{';
		key.loadFromFile("data/png/2_12.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==93)
	{
		string ss="]";
		s=s+ss;
		type_sound.play();
		input[for_in]=']';
		key.loadFromFile("data/png/2_13.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==125)
	{
		string ss="}";
		s=s+ss;
		type_sound.play();
		input[for_in]='}';
		key.loadFromFile("data/png/2_13.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==92)
	{
		string ss="\\";
		s=s+ss;
		type_sound.play();
		input[for_in]='\\';
		key.loadFromFile("data/png/2_14.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==124)
	{
		string ss="|";
		s=s+ss;
		type_sound.play();
		input[for_in]='|';
		key.loadFromFile("data/png/2_14.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==59)
	{
		string ss=";";
		s=s+ss;
		type_sound.play();
		input[for_in]=';';
		key.loadFromFile("data/png/3_11.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==58)
	{
		string ss=":";
		s=s+ss;
		type_sound.play();
		input[for_in]=':';
		key.loadFromFile("png/3_11.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==39)
	{
		string ss="\'";
		s=s+ss;
		type_sound.play();
		input[for_in]='\'';
		key.loadFromFile("data/png/3_12.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==34)
	{
		string ss="\"";
		s=s+ss;
		type_sound.play();
		input[for_in]='\"';
		key.loadFromFile("data/png/3_12.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==44)
	{
		string ss=",";
		s=s+ss;
		type_sound.play();
		input[for_in]=',';
		key.loadFromFile("data/png/4_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==60)
	{
		string ss="<";
		s=s+ss;
		type_sound.play();
		input[for_in]='<';
		key.loadFromFile("data/png/4_9.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==46)
	{
		string ss=".";
		s=s+ss;
		type_sound.play();
		input[for_in]='.';
		key.loadFromFile("data/png/4_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==62)
	{
		string ss=">";
		s=s+ss;
		type_sound.play();
		input[for_in]='>';
		key.loadFromFile("data/png/4_10.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==47)
	{
		string ss="/";
		s=s+ss;
		type_sound.play();
		input[for_in]='/';
		key.loadFromFile("data/png/4_11.png", IntRect(2, 2, 1274, 282));
	}

	if	(event.text.unicode==63)
	{
		string ss="?";
		s=s+ss;
		type_sound.play();
		input[for_in]='?';
		key.loadFromFile("data/png/4_11.png", IntRect(2, 2, 1274, 282));
	}
	if	(event.text.unicode==32)
	{
		string ss=" ";
		s=s+ss;
		key.loadFromFile("data/png/5_3.png", IntRect(2, 2, 1274, 282));
		type_sound.play();
		input[for_in]=' ';
		num_word++;
		i++;
		s.clear();
}
	if (input[for_in]==output[for_out])
{
	for_in++;
	for_out++;
	score++;
	wslide_position=wslide_position-10;
	man_position=man_position+60;
	cout << "right" << endl;
}
if (input[for_in]!=output[for_out])
{
	for_in++;
	for_out++;
	wslide_position=wslide_position-10;
	cout<< "wrong"<< endl; 
}
	case Event::KeyReleased:
	if (event.type == sf::Event::KeyReleased)
	{
	key.loadFromFile("data/png/key.png", IntRect(2, 2, 1274, 282));
	


}

	break;

}

}

current_word.setString(words[num_word]);
///////////////////////////////////////set keyboard sprite///////////////////////////////////
sprite_keyboard.setTexture(key);
//////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////slide man/////////////////

Time word_slide_time=word_slide_clock.getElapsedTime();
secs=word_slide_time.asMilliseconds();
temp=man_position-(secs*0.1);
man.setPosition(temp,200);
if (temp>1200)
{
	man_position=1200;
	word_slide_clock.restart();
	//temp=1200;
} 
	
man.setPosition(temp,200);

/////////////////////////////////////////////////////////////////////////////////////////////////
		
		if (xtra_life>=10)
	{
		lives++;
		xtra_life=0;
	}
//////////////////////////////////////for main clock///////////////////////////////////////////
Time game_time = game_clock.getElapsedTime();
sec_ten = game_time.asSeconds();


if (sec_ten==10)
{
	sec++;
	game_clock.restart();
}
if (sec==6)
{
	minute++;
	sec=0;
}
if (minute==10)
{
minute_ten++;
minute=0;
}
if(minute_ten==6)
{
hour++;
minute_ten=0;
}

display_sec_ten.setString(intstr(sec_ten));
display_sec.setString(intstr(sec));
display_min_ten.setString(intstr(minute));
display_min.setString(intstr(minute_ten));
display_score.setString(intstr(score));
display_lives.setString(intstr(lives));
///////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////for typing speed///////////////////////////////////////////////
Time word_count_time = word_count_clock.getElapsedTime();
if(word_count_time.asSeconds() >= 15)
{
	j=i;
	i=0;
	word_count_clock.restart();
}
display_wordspeed.setString(intstr(j*4));

///////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////user input  on screen/////////////////////////////////////////////
text_user_input.setString(s);
/////////////////////////////////////////////////////position for sliding word/////////////////////////////////////////////////
string_slide.setPosition(wslide_position, 270);

////////////////////////////////////////////////////////////////////////////////////////////////////////





if (temp == 80)
{
	window.close();
}

if(level_update==100)
{
	level=medium;
}
if(level_update==200)
{
	level=hard;
}


window.clear();
window.draw(sprite);
if (level!=hard)
{
	window.draw(sprite_keyboard);
}
window.draw(typeline);
window.draw(text_time);
window.draw(text_speed);
window.draw(display_sec_ten);
window.draw(display_sec);
window.draw(text_seperator);
window.draw(display_min_ten);
window.draw(display_min);
window.draw(display_wordspeed);
window.draw(text_user_input);
window.draw(text_score);
window.draw(display_score);
//window.draw(text_lives);
//window.draw(display_lives);
window.draw(input_string);
window.draw(string_slide);
window.draw(current_word);
window.draw(shark);
window.draw(man);
window.display();
}
return 0;
}


int highscore_window()
{
	RenderWindow window(VideoMode(1280, 720), "Highscore", Style::Titlebar | Style::Close);

	Font font;
	font.loadFromFile("data/font/arial.ttf");
	if(!font.loadFromFile("data/font/arial.ttf"))
	{
		cerr << "Couldn't load font" << endl;
	}

SoundBuffer back_buffer;
back_buffer.loadFromFile("data/sound/back.wav");
Sound back_sound;
back_sound.setBuffer(back_buffer);

	Texture texture;
	texture.loadFromFile("data/png/3.png", IntRect(0, 0, 1280, 760));
	Sprite sprite;
	sprite.setTexture(texture);

Text first;
first.setFont(font);
first.setString("1)  "+ str_highscore[0]);
first.setCharacterSize(20);
first.setColor(Color(255,255,255));
first.setStyle(Text::Bold);
first.setPosition(100, 120);

Text second;
second.setFont(font);
second.setString("2)  "+ str_highscore[1]);
second.setCharacterSize(20);
second.setColor(Color(255,255,255));
second.setStyle(Text::Bold);
second.setPosition(100, 170);

Text third;
third.setFont(font);
third.setString("3)  "+ str_highscore[2]);
third.setCharacterSize(20);
third.setColor(Color(255,255,255));
third.setStyle(Text::Bold);
third.setPosition(100, 220);


Text fourth;
fourth.setFont(font);
fourth.setString("4)  "+ str_highscore[3]);
fourth.setCharacterSize(20);
fourth.setColor(Color(255,255,255));
fourth.setStyle(Text::Bold);
fourth.setPosition(100, 270);

Text fifth;
fifth.setFont(font);
fifth.setString("5)  "+ str_highscore[4]);
fifth.setCharacterSize(20);
fifth.setColor(Color(255,255,255));
fifth.setStyle(Text::Bold);
fifth.setPosition(100, 320);


Text sixth;
sixth.setFont(font);
sixth.setString("6)  "+ str_highscore[5]);
sixth.setCharacterSize(20);
sixth.setColor(Color(255,255,255));
sixth.setStyle(Text::Bold);
sixth.setPosition(100, 370);

Text seventh;
seventh.setFont(font);
seventh.setString("7)  "+ str_highscore[6]);
seventh.setCharacterSize(20);
seventh.setColor(Color(255,255,255));
seventh.setStyle(Text::Bold);
seventh.setPosition(100, 420);

Text eight;
eight.setFont(font);
eight.setString("8)  "+ str_highscore[7]);
eight.setCharacterSize(20);
eight.setColor(Color(255,255,255));
eight.setStyle(Text::Bold);
eight.setPosition(100, 470);

Text ninth;
ninth.setFont(font);
ninth.setString("9)  "+ str_highscore[8]);
ninth.setCharacterSize(20);
ninth.setColor(Color(255,255,255));
ninth.setStyle(Text::Bold);
ninth.setPosition(100, 520);

Text tenth;
tenth.setFont(font);
tenth.setString("10)  "+ str_highscore[9]);
tenth.setCharacterSize(20);
tenth.setColor(Color(255,255,255));
tenth.setStyle(Text::Bold);
tenth.setPosition(100, 570);

	Event event;
	while (window.isOpen())
	{


		while (window.pollEvent(event))

		{
		switch (event.type)
			{
		case Event::Closed:
		window.close();
		break;
		}
		if(Keyboard::isKeyPressed(Keyboard::Space))
		{
		    back_sound.play();
		    window.close();
			front_window();
			return 0;
		}

	}
	window.clear();
	window.draw(sprite);
	window.draw(first);
	window.draw(second);
	window.draw(third);
	window.draw(fourth);
	window.draw(fifth);
	window.draw(sixth);
	window.draw(seventh);
	window.draw(eight);
	window.draw(ninth);
	window.draw(tenth);
	window.display();
}
return 0;
}


int display_highscore_window()
{
	//score_rank(int z);
	RenderWindow window(VideoMode(1280, 720), "Highscore", Style::Titlebar | Style::Close);

	Font font;
	font.loadFromFile("data/font/arial.ttf");
	if(!font.loadFromFile("data/font/arial.ttf"))
	{
		cerr << "Couldn't load font" << endl;
	}

	Texture texture;
	texture.loadFromFile("data/png/3.png", IntRect(0, 0, 1280, 760));
	Sprite sprite;
	sprite.setTexture(texture);

SoundBuffer rank_buffer;
rank_buffer.loadFromFile("data/sound/rank.wav");
Sound rank_sound;
rank_sound.setBuffer(rank_buffer);
rank_sound.play();

SoundBuffer back_buffer;
back_buffer.loadFromFile("data/sound/back.wav");
Sound back_sound;
back_sound.setBuffer(back_buffer);

Text first;
first.setFont(font);
first.setString("1)  "+ str_highscore[0]);
first.setCharacterSize(20);
first.setColor(Color(255,255,255));
first.setStyle(Text::Bold);
first.setPosition(100, 120);

Text second;
second.setFont(font);
second.setString("2)  "+ str_highscore[1]);
second.setCharacterSize(20);
second.setColor(Color(255,255,255));
second.setStyle(Text::Bold);
second.setPosition(100, 170);

Text third;
third.setFont(font);
third.setString("3)  "+ str_highscore[2]);
third.setCharacterSize(20);
third.setColor(Color(255,255,255));
third.setStyle(Text::Bold);
third.setPosition(100, 220);


Text fourth;
fourth.setFont(font);
fourth.setString("4)  "+ str_highscore[3]);
fourth.setCharacterSize(20);
fourth.setColor(Color(255,255,255));
fourth.setStyle(Text::Bold);
fourth.setPosition(100, 270);

Text fifth;
fifth.setFont(font);
fifth.setString("5)  "+ str_highscore[4]);
fifth.setCharacterSize(20);
fifth.setColor(Color(255,255,255));
fifth.setStyle(Text::Bold);
fifth.setPosition(100, 320);


Text sixth;
sixth.setFont(font);
sixth.setString("6)  "+ str_highscore[5]);
sixth.setCharacterSize(20);
sixth.setColor(Color(255,255,255));
sixth.setStyle(Text::Bold);
sixth.setPosition(100, 370);

Text seventh;
seventh.setFont(font);
seventh.setString("7)  "+ str_highscore[6]);
seventh.setCharacterSize(20);
seventh.setColor(Color(255,255,255));
seventh.setStyle(Text::Bold);
seventh.setPosition(100, 420);

Text eight;
eight.setFont(font);
eight.setString("8)  "+ str_highscore[7]);
eight.setCharacterSize(20);
eight.setColor(Color(255,255,255));
eight.setStyle(Text::Bold);
eight.setPosition(100, 470);

Text ninth;
ninth.setFont(font);
ninth.setString("9)  "+ str_highscore[8]);
ninth.setCharacterSize(20);
ninth.setColor(Color(255,255,255));
ninth.setStyle(Text::Bold);
ninth.setPosition(100, 520);

Text tenth;
tenth.setFont(font);
tenth.setString("10)  "+ str_highscore[9]);
tenth.setCharacterSize(20);
tenth.setColor(Color(255,255,255));
tenth.setStyle(Text::Bold);
tenth.setPosition(100, 570);

	Event event;
	while (window.isOpen())
	{


		while (window.pollEvent(event))

		{
		switch (event.type)
			{
		case Event::Closed:
		window.close();
		break;
		}
		if(Keyboard::isKeyPressed(Keyboard::Space))
		{
		    back_sound.play();
			window.close();
			front_window();
			return 0;
		}


	}
	if (rank==1)
	{
		first.setColor(Color(255,0,0));
	}
	if (rank==2)
	{
		second.setColor(Color(255,0,0));
	}
	if (rank==3)
	{
		third.setColor(Color(255,0,0));
	}
	if (rank==4)
	{
		fourth.setColor(Color(255,0,0));
	}
	if (rank==5)
	{
		fifth.setColor(Color(255,0,0));
	}
	if (rank==6)
	{
		sixth.setColor(Color(255,0,0));
	}
	if (rank==7)
	{
		seventh.setColor(Color(255,0,0));
	}
	if (rank==8)
	{
		eight.setColor(Color(255,0,0));
	}
	if (rank==9)
	{
		ninth.setColor(Color(255,0,0));
	}
	if (rank==10)
	{
		tenth.setColor(Color(255,0,0));
	}

	window.clear();
	window.draw(sprite);
	window.draw(first);
	window.draw(second);
	window.draw(third);
	window.draw(fourth);
	window.draw(fifth);
	window.draw(sixth);
	window.draw(seventh);
	window.draw(eight);
	window.draw(ninth);
	window.draw(tenth);
	window.display();
}
return 0;
}

/*int credit_window()

 {
	RenderWindow window(VideoMode(1280, 720), "Highscore", Style::Titlebar | Style::Close);

	Texture texture;
	texture.loadFromFile("data/png/4.png");
	Sprite sprite;
	sprite.setTexture(texture);

	 event;
	while (window.isOpen())
	{


		while (window.pollEvent(event))

		{
		switch (event.type)
			{
		case Event::Closed:
		window.close();
		break;
		}
		if(Keyboard::isKeyPressed(Keyboard::Space))
		{
			window.close();
			front_window();
			return 0;
		}
	}
	window.clear();
	window.draw(sprite);
	window.display();
}

return 0;
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





int main()

{
	get_score();
	str_to_int();
	fill_words_bank();
	front_window();
	return 0;
}
