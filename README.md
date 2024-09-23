# Pipeline
## Esta é uma Atividade Prática de programação
Usando pipes como mecanismo de comunicação entre processos, crie um programa que execute o seguinte procedimento:
- O processo pai, P0, lê do teclado um valor X inteiro entre 1-5.
- O processo pai, P0, lê do teclado um segundo valor Y inteiro entre 6 e 10.
- P0 cria três filhos, P1, P2 e P3.
- P0 envia para o filho P1 via pipe (pipe1) o valor de X.
- P0 envia para o filho P2 via pipe (pipe2) o valor de Y.
- P0 envia para P1, pelo mesmo pipe1, a seguinte mensagem (string): "Meu filho, crie e envie para o seu irmão P3 um array de tamanho randômico entre 100 e 200, preenchido completamente com o valor X" (obs: ele envia o valor de X e não a letra 'X').
- P0 envia para P2, pelo mesmo pipe2, a seguinte mensagem (string): "Meu filho, crie e envie para o seu irmão P3 um array de tamanho randômico entre 100 e 200, preenchido completamente com o valor Y" (obs: ele envia o valor de Y e não a letra 'Y').
- P1 e P2 recebem e imprimem a mensagem enviada pelo pai (identifique se é P1 ou P2 quem printa cada mensagem).
- P1 e P2 criam seus arrays de tamanho randômico, entre 100 e 200, preenchendo-os com valores X (no caso de P1) e Y (no caso de P2), conforme solicitado pelo pai.
- P1 e P2 enviam os arrays para o irmão P3, via pipe3 (sim... eles usarão o mesmo pipe!! mas cuidado! as escritas podem se embaralhar.... resolvam isso!).
- P3 lê os dois arrays enviados e printa os arrays na saída padrão. 
