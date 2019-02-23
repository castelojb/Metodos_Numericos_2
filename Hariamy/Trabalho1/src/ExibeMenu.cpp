#include "../header/ExibeMenu.h"

using namespace std;

void exibeMenu(){
	system("clear");
	system("clear");

	cout << COR_CIANO;
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	cout << "                                                          ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	cout << "                    ╔════════════════╗                    ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	cout << "   ╔════════════════╣      MENU      ╠════════════════╗   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	cout << "   ║                ╚════════════════╝                ║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	cout << "   ║                                                  ║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	
	cout << "   ║";
	cout << COR_VERMELHO;
	cout <<       "      TECLA              FUNÇÃO                   ";
	cout << COR_CIANO <<                                         "║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;


	cout << "   ║                                                  ║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	

	cout << "   ║";
	cout << COR_PRETO;
	cout <<       "      ESPAÇO         Troca Imagem                ";
	cout << COR_CIANO <<                                         "║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;


	cout << "   ║";
	cout << COR_AZUL;
	cout <<       "        A            Imagem Anterior              ";
	cout << COR_CIANO <<                                         "║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	
	
	cout << "   ║";
	cout << COR_PRETO;
	cout <<       "        B            Próxima Imagem               ";
	cout << COR_CIANO <<                                         "║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;


	cout << "   ║                                                  ║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	
	cout << "   ║";
	cout << COR_AZUL;
	cout <<       "        +            Aumenta precisão             ";
	cout << COR_CIANO <<                                         "║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	
	cout << "   ║";
	cout << COR_PRETO;
	cout <<       "        -            Diminui precisão             ";
	cout << COR_CIANO <<                                         "║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	
	cout << "   ║                                                  ║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;

	cout << "   ║";
	cout << COR_AZUL;
	cout <<       "        C            Colorido/Preto e branco      ";
	cout << COR_CIANO <<                                         "║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;

	cout << "   ║                                                  ║   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	cout << "   ╚══════════════════════════════════════════════════╝   ";
	cout << FUNDO_NORMAL << "\n  " << FUNDO_BRANCO;
	cout << "                                                          ";
	cout << COR_NORMAL;
	cout << FUNDO_NORMAL;
	cout << "\n\n";

}

void limpaMenu() {
	system("clear");
	system("clear");
	system("clear");
}