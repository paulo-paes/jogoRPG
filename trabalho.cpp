#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

/*
  Ao fim de cada turno é necessário apertar a tecla enter para continuar para o próximo turno

  Um turno acaba quando todos os personagens lutam
*/

class Personagem
{
protected:
  string nome;
  int vida;
  int _vida;
  int ataque;
  int defesa;
  Personagem *derrotados[16];
  int numDerrotados = 0;
  int danoCausado = 0;
  int danoRecebido = 0;
  int maiorDanoRecebido = 0;
  int maiorDanoCausado = 0;
  bool sangramento = false;
  int roundsSangramento = 0; // Rounds restantes
  int danoRecebidoRound = 0;
  int danoCausadoRound = 0;
  int atqEspecialRound = 0;

public:
  Personagem(string nome, int vida, int ataque, int defesa)
  {
    this->nome = nome;
    this->vida = vida;
    this->_vida = vida;
    this->ataque = ataque;
    this->defesa = defesa;
  }

  virtual int ataqueEspecial()
  {
    return this->ataque;
  }

  void ligarSangramento()
  {
    if (!sangramento)
    {
      sangramento = true;
      roundsSangramento = (rand() % 5) + 2;
    }
  }

  bool computarSangramento()
  {
    if (sangramento && roundsSangramento > 0)
    {
      this->vida -= 5;
      roundsSangramento--;
      cout << this->nome << " Está sangrando..." << endl;
    }

    if (roundsSangramento <= 0)
    {
      this->sangramento = false;
      this->roundsSangramento = 0;
    }

    if (this->vida <= 0)
    {
      this->vida = 0;
    }

    return this->derrotado();
  }

  void exibirEstatisticas()
  {
    cout << "Nome: " << nome << endl;
    cout << "Classe: " << this->getClasse() << endl;
    cout << "Vida: " << vida << endl;
    cout << "Ataque: " << ataque << endl;
    cout << "Defesa: " << defesa << endl;
    cout << "Derrotados: ";
    for (int i = 0; i < numDerrotados; i++)
    {
      cout << derrotados[i]->getNome() << " " << derrotados[i]->getClasse() << endl;
    }
    cout << endl;
  }

  void exibirEstatisticasVencedor()
  {
    cout << "Nome: " << nome << endl;
    cout << "Classe: " << this->getClasse() << endl;
    cout << "Vida: " << vida << endl;
    cout << "Ataque: " << ataque << endl;
    cout << "Defesa: " << defesa << endl;
    cout << "Dano total causado: " << danoCausado << endl;
    cout << "Maior dano causado em um round: " << maiorDanoCausado << endl;
    cout << "Dano total sofrido: " << danoRecebido << endl;
    cout << "Maior dano sofrido em um round: " << maiorDanoRecebido << endl;
    cout << "Derrotados: ";
    for (int i = 0; i < numDerrotados; i++)
    {
      cout << derrotados[i]->getNome() << " " << derrotados[i]->getClasse() << endl;
    }
    cout << endl;
  }

  string getNome()
  {
    return this->nome;
  }

  int getVida()
  {
    return vida;
  }

  void setVida(int vida)
  {
    this->vida = vida;
  }

  int getAtaque()
  {
    return ataque;
  }

  int getDefesa()
  {
    return defesa;
  }

  int getAtqEspecialRound() {
    return this->atqEspecialRound;
  }

  void adicionarDanoCausado(int dano)
  {
    if (dano > 0)
    {
      this->danoCausado += dano;
      if (dano > maiorDanoCausado)
      {
        maiorDanoCausado = dano;
      }
    }
  }

  void adicionarDanoRecebido(int dano)
  {
    if (dano > 0)
    {
      this->danoRecebido += dano;
      if (dano > maiorDanoRecebido)
      {
        maiorDanoRecebido = dano;
      }
    }
  }

  void recebeAtaque(int dano)
  {
    if (dano < 0)
    {
      return;
    }
    this->vida -= dano;
    if (dano > 0)
    {
      this->danoRecebido += dano;
      if (dano > this->maiorDanoRecebido)
      {
        this->maiorDanoRecebido = dano;
      }
      this->danoRecebidoRound += dano;
    }
    if (this->vida <= 0)
    {
      this->vida = 0;
    }
  }

  bool atacar(Personagem *alvo)
  {
    int dano;
    if ((rand() % 100) >= 85)
    {
      dano = ataqueEspecial() - alvo->getDefesa();
      alvo->ligarSangramento();
      atqEspecialRound += 1;
    }
    else
    {
      dano = ataque + (rand() % 5) - alvo->getDefesa();
    }
    if (dano > 0)
    {
      this->danoCausado += dano;
      if (dano > this->maiorDanoCausado)
      {
        this->maiorDanoCausado = dano;
      }

      this->danoCausadoRound += dano;
    }
    cout << this->nome << " Ataca " << alvo->getNome() << " Causando " << dano << " de dano" << endl;
    if (dano > 0)
    {
      alvo->recebeAtaque(dano);
    }

    return alvo->derrotado();
  }

  bool derrotado()
  {
    return vida == 0;
  }

  void adicionarDerrotado(Personagem *derrotado)
  {
    if (numDerrotados < 16)
    { // Verificar se há espaço disponível no array
      derrotados[numDerrotados] = derrotado;
      numDerrotados++;
    }
  }

  void resetVida()
  {
    this->vida = _vida;
    this->danoCausadoRound = 0;
    this->danoRecebidoRound = 0;
    this->atqEspecialRound = 0;
  }

  virtual string getClasse()
  {
    return "";
  }

  int getDanoRound()
  {
    return this->danoCausadoRound;
  }

  int getDanoRecebidoRound()
  {
    return this->danoRecebidoRound;
  }
};

class Guerreiro : public Personagem
{
public:
  Guerreiro(string nome, int vida, int ataque, int defesa) : Personagem(nome, vida, ataque, defesa) {}

  string getClasse() override
  {
    return "Guerreiro";
  }

  int ataqueEspecial() override
  {
    cout << this->nome << " utiliza Ataque Especial Golpe da Fúria" << endl;
    return this->ataque * 1.5;
  }
};

class Bruxo : public Personagem
{
public:
  Bruxo(string nome, int vida, int ataque, int defesa) : Personagem(nome, vida, ataque, defesa) {}

  string getClasse() override
  {
    return "Bruxo";
  }

  int ataqueEspecial() override
  {
    cout << this->nome << " utiliza Ataque Especial Invocação do Abismo" << endl;
    return this->ataque * 1.5;
  }
};

class Ladrao : public Personagem
{
public:
  Ladrao(string nome, int vida, int ataque, int defesa) : Personagem(nome, vida, ataque, defesa) {}
  string getClasse() override
  {
    return "Ladrão";
  }

  int ataqueEspecial() override
  {
    cout << this->nome << " utiliza Ataque Especial Golpe das Sombras" << endl;
    return this->ataque * 1.5;
  }
};

class Arqueiro : public Personagem
{
public:
  Arqueiro(string nome, int vida, int ataque, int defesa) : Personagem(nome, vida, ataque, defesa) {}
  string getClasse() override
  {
    return "Arqueiro";
  }

  int ataqueEspecial() override
  {
    cout << this->nome << " utiliza Ataque Especial Flecha mortal" << endl;
    return this->ataque * 1.5;
  }
};

class Monge : public Personagem
{
public:
  Monge(string nome, int vida, int ataque, int defesa) : Personagem(nome, vida, ataque, defesa) {}

  string getClasse() override
  {
    return "Monge";
  }

  int ataqueEspecial() override
  {
    cout << this->nome << " utiliza Ataque Especial Punho da Serenidade" << endl;
    return this->ataque * 1.5;
  }
};

class Clerigo : public Personagem
{
public:
  Clerigo(string nome, int vida, int ataque, int defesa) : Personagem(nome, vida, ataque, defesa) {}
  string getClasse() override
  {
    return "Clerigo";
  }

  int ataqueEspecial() override
  {
    cout << this->nome << " utiliza Ataque Especial Crepúsculo divino" << endl;
    return this->ataque * 1.5;
  }
};

class Turno
{
private:
  Personagem *personagens[16];
  int lutaram[16];
  int iLutaram;
  int countDisponiveis = 0; // Contagem para saber quantos personagens estão na disputa. 0-based
  int nTurno;

public:
  Turno(Personagem *perso[16], int nTurno)
  {
    this->nTurno = nTurno;
    cout << "TURNO " << nTurno << " COMEÇANDO" << endl;
    int j = countDisponiveis;
    for (int i = 0; i < 16; i++)
    {
      if (!(perso[i]->derrotado()))
      {
        personagens[j] = perso[i];
        j++;
      }
    }

    for (int i = j; i < 16; i++)
    {
      personagens[i + 1] = nullptr;
    }

    countDisponiveis = j;
  }

  void iniciarTurno()
  {
    for (int i = 0; i < countDisponiveis; i += 2)
    {
      if (
          (i + 1) >= countDisponiveis ||
          (personagens[i] == nullptr || personagens[i + 1] == nullptr))
      {
        continue;
      }
      Personagem *atacante = personagens[i];
      Personagem *alvo = personagens[i + 1];

      int round = 0;
      bool limiteExcedido = false;

      while (!(atacante->derrotado() || alvo->derrotado()))
      {
        bool derrotado1 = atacante->computarSangramento();
        bool derrotado2 = alvo->computarSangramento();

        if (derrotado1 && derrotado2)
        {
          cout << "Ambos Personagens foram derrotados por Sangramento" << endl;
          break;
        }
        else if (derrotado1 || derrotado2)
        {
          break;
        }

        if (rand() % 2 == 0)
        {
          derrotado1 = atacante->atacar(alvo);
          if (derrotado1)
          {
            break;
          }
          alvo->atacar(atacante);
        }
        else
        {
          derrotado2 = alvo->atacar(atacante);
          if (derrotado2)
          {
            break;
          }

          atacante->atacar(alvo);
        }

        round++;

        if (round >= 10)
        {
          limiteExcedido = true;
          cout << "Limite excedido" << endl;
          break;
        }
      }

      cout << "Combate Encerrado" << endl;
      cout << "Rounds: " << round << endl;
      cout << atacante->getNome() << " causou " << atacante->getDanoRound();
      cout << " de dano e recebeu " << atacante->getDanoRecebidoRound() << endl;
      cout << "Quantidade de ataques especiais neste turno: " << atacante->getAtqEspecialRound() << endl;
      cout << alvo->getNome() << " causou " << alvo->getDanoRound();
      cout << " de dano e recebeu " << alvo->getDanoRecebidoRound() << endl;
      cout << "Quantidade de ataques especiais neste turno: " << alvo->getAtqEspecialRound() << endl;

      Personagem *vencedor = nullptr;
      Personagem *derrotado = nullptr;

      if (limiteExcedido)
      {
        if (atacante->getVida() > alvo->getVida())
        {
          vencedor = atacante;
          derrotado = alvo;
        }
        else
        {
          vencedor = alvo;
          derrotado = atacante;
        }

        derrotado->setVida(0);
      }
      else
      {
        if (atacante->derrotado() && alvo->derrotado())
        {
          cout << "Ambos derrotados" << endl;
        }
        else if (atacante->derrotado())
        {
          vencedor = alvo;
          derrotado = atacante;
        }
        else
        {
          vencedor = atacante;
          derrotado = alvo;
        }
      }

      if (vencedor != nullptr && derrotado != nullptr)
      {
        cout << derrotado->getNome() << " foi derrotado!" << endl;
        vencedor->adicionarDerrotado(derrotado);
        vencedor->exibirEstatisticas();
        vencedor->resetVida();
      }
    }
    cout << "FIM DO TURNO " << nTurno << endl;
  }
};

class JogoRPG
{
private:
  int tamanho = 16;
  Personagem *personagens[16];
  int contagemPersonagens = 0;
  int derrotados = 0;

public:
  JogoRPG()
  {
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < tamanho; i++)
    {
      int vida = rand() % 101 + 15;
      int ataque = rand() % 31;
      int defesa = rand() % 16;
      this->criarPersonagem("Personagem " + to_string(i), vida + 1, ataque + 1, defesa + 1);
    }
  }
  void criarPersonagem(string nome, int vida, int defesa, int ataque)
  {
    if (contagemPersonagens < 3)
    {
      personagens[contagemPersonagens] = new Guerreiro(nome, vida, defesa, ataque);
    }
    else if (contagemPersonagens < 6)
    {
      personagens[contagemPersonagens] = new Bruxo(nome, vida, defesa, ataque);
    }
    else if (contagemPersonagens < 9)
    {
      personagens[contagemPersonagens] = new Ladrao(nome, vida, defesa, ataque);
    }
    else if (contagemPersonagens < 12)
    {
      personagens[contagemPersonagens] = new Arqueiro(nome, vida, defesa, ataque);
    }
    else if (contagemPersonagens < 15)
    {
      personagens[contagemPersonagens] = new Monge(nome, vida, defesa, ataque);
    }
    else
    {
      personagens[contagemPersonagens] = new Clerigo(nome, vida, defesa, ataque);
    }
    contagemPersonagens++;
  }

  void calcularDerrotados()
  {
    this->derrotados = 0;
    for (int i = 0; i < tamanho; i++)
    {
      if (personagens[i]->derrotado())
      {
        derrotados++;
      }
    }

    cout << "Total derrotados " << this->derrotados << endl;
  }

  void iniciar()
  {
    int countTurno = 1;
    while (tamanho - derrotados > 1)
    {
      Turno turn = Turno(this->personagens, countTurno);

      turn.iniciarTurno();
      calcularDerrotados();
      cout << "Pressione enter para continuar...";
      cin.get();

      countTurno++;
    }

    int vencedorIndex = -1;

    for (int i = 0; i < tamanho; i++)
    {
      if (!personagens[i]->derrotado())
      {
        vencedorIndex = i;
        break;
      }
    }

    if (vencedorIndex != -1)
    {
      cout << "O vencedor é: " << personagens[vencedorIndex]->getNome() << endl;
      personagens[vencedorIndex]->exibirEstatisticasVencedor();
    }
    else
    {
      cout << "Não houve vencedor." << endl;
    }
  }
};

int main()
{
  JogoRPG jogo;

  jogo.iniciar();
}