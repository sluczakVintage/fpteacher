#include "CAnimation.hpp"

// konstruktor domyslny
CAnimation::CAnimation() : numberOfFrames_(0)
{
	cout << "CAnimation::CAnimation: Konstruktor CAnimation" << endl;
}

// konstruktor z pliku
CAnimation::CAnimation(const string filename) : numberOfFrames_(0)
{
	cout << "CAnimation::CAnimation: Konstruktor CAnimation z pliku" << endl;
	openFile(filename);
}

// metoda otwierajaca plik i pobierajaca z niej animacje
bool CAnimation::openFile(const string filename)
{
	string s;
	string filename_prefix;
	size_t found;

	// pozyskanie prefiksu folderu z animacja
	found = filename.find_last_of("\\");
	filename_prefix = filename.substr(0,found);
	filename_prefix.append("\\");

	// kolejka 2 stronna zawierajaca odstepy miedzy klatkami
	queue<float> temp_delays;
	// szerokosc paska animacji
	int slice_w;
	{
		ifstream in(filename.c_str());
		
		try
		{
		if(!in) {
			throw utils::BadFileError("CAnimation::openFile(): Nie otwarto pliku animacji!");
			return false;
		  }
		} 	catch (utils::BadFileError& x) {
			cerr << "BadFileError: " << x.what() << endl;
			throw;
		}

		// proste pobieranie danych ze strumienia oparte na poszukiwaniu znacznikow
		while( getline(in, s) ) {

			istringstream data(s);
			string token;
			// pobierz ze strumienia pierwsza dana, ktora powinna byc token'em
			data >> token;
			cout << token << endl;
			if( token == "SPRITE") {
				string temp;
				//przytnij
				data.ignore(20, '='); 
				data >> temp;
				// dodaj prefiks do zmiennej z nazwa
				animSetName_ = filename_prefix;
				// i sama nazwe
				animSetName_.append(temp);
				cout << animSetName_ << endl; 
			}
			else if( token == "SLICE_W") {
				//przytnij
				data.ignore(20, '=');
				//pobierz szerokosc paska
				data >> slice_w;
				cout << slice_w << endl;
			}
			else if( token == "NUMOFFRAMES") {
				//przytnij
				data.ignore(20, '=');
				//pobierz liczbe klatek
				data >> skipws >> numberOfFrames_;
				cout << numberOfFrames_ << endl;
			}
			else if( token == "DELAYS") {
				//przytnij
				data.ignore(20, '=');
				//pobierz kolejne czasy klatek
				for(int i = 1; i <= numberOfFrames_; i++) {
					float delay;
					// i wstaw do kolejki z pominieciem bialych znakow
					data >> skipws >> delay;
					temp_delays.push(delay);
					cout << delay << endl;
				}
			}
		}
	}
	// Ciecie plikow graficznych
	HCSprite temp_sprite_handle;
	//kolejno stworz CSprite'y skladowe animacji i przypisz odpowiadajace im czasy trwania klatek
	for( int i = 1; i <= numberOfFrames_; i++) {
		temp_sprite_handle = CSpriteMgr::getInstance()->getCSprite(animSetName_, i, slice_w);
		animSet_.push_back(std::make_pair(temp_sprite_handle, temp_delays.front()));
		temp_delays.pop();
	}
	if(numberOfFrames_ == static_cast<int>(animSet_.size() ) ) 
	{	
		cout << "CAnimation::openFile: Ladowanie animacji sie powiodlo." << endl;
		return true;
	}
	else
	{
		cerr << "CAnimation::openFile: Ladowanie animacji sie nie powiodlo!" << endl;
		return false;
	}
}

// zwolnij wektor z uchwytami do klatek animacji i odstepami
void CAnimation::releaseAnimation()
{
	animSet_.erase(animSet_.begin(), animSet_.end());
	animSet_.clear();
	cout << "CAnimation::releaseAnimation: Wektor uchwytów zniszczony" << endl;
}

// pobierz opoznienie dla danej ramki
float CAnimation::getDelayOf(int frame) const
{
	return animSet_[frame].second;
}

// pobierz liczbe klatek animacji
int CAnimation::getNoOfAnimationFrames() const
{
	return numberOfFrames_;
}

// pobierz nazwe animacji
const string& CAnimation::getAnimationName() const
{
	return animSetName_;
}

// pobierz pare sprite + jego opoznienie
const vector< pair< HCSprite, float > >& CAnimation::getAnimSet() const
{
	return animSet_;
}

//~~CAnimation.cpp
