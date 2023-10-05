## Comando para gerar o executavel

gcc -o trabalho trabalho.cpp -lstdc++

or

g++ -o trabalho trabalho.cpp

./trabalho

## Anotações

Ao fim de cada turno é necessário apertar a tecla enter para continuar para o próximo turno

Um turno acaba quando todos os personagens lutam


## O que foi implementado:

Foram implementados todos os requisitos exigidos

Existem 6 Arquetipos disponíveis Guerreiro, Arqueiro, Bruxo, Monge, Clérigo e Ladrão.
O código principal está na classe Personagem que os arquetipos herdam.
Nas classes dos Arquetipos estão definidos apenas os metodos de obter o nome do Arquetipo e um metodo para obter o nome e dano do ataque especial.

Também existem as classes JogoRPG que é responsável por criar os personagens e dar inicio aos turnos. E computar o vencedor.
A classe Turno gerencia as lutas e provê as estatíscas de combate de cada turno.

Fluxo da aplicação:

A função main inicia o jogo através da classe JogoRPG, através do Construtor ela cria os personagens. Após Iniciar o jogo o método entra em Loop até que reste um Personagem, ela fica chamando a classe Turno a cada iteração e executando os combates daquele Turno.

No construtor da classe turno ela copia o array de personagens da classe JogoRPG mas não contabiliza os personagens derrotados. No método iniciar turno da classe Turno ela gerencia as duplas de combate gerando os ataques, a cada round um personagem é sorteado para começar atacando após a contagem de sangramento caso o combate exceda 10 Rounds quem estiver com menos vida é eliminado.

É necessário ao fim de cada turno apertar a tecla enter para iniciar o próximo turno. Também ao fim de cada combate são exibidos os dados do combate e as estátisticas do vencedor do combate.

Quando restar apenas 1 Personagem ou todos forem derrotados o Jogo é finalizado e é exibidos as estatísticas do vencedor.