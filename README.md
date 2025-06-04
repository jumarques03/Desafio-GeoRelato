# Desafio-GeoRelato
Este repositório contém o Desafio GeoRelato: uma CLI para registrar catástrofes naturais em um raio de 10 km de um ponto central. Permite cadastrar relatores e ocorrências (com validação de localização), e oferece busca e listagem por tipo, local e período. 

## Estrutura do Sistema

### 1. Structs utilizadas
- `Relator`: Armazena os dados da pessoa relatora (nome, CPF, e-mail, telefone, localização com lat e lon).
- `Relato`: Armazena informações sobre o relato (tipo, descrição, data, hora, localização com lat e lon).

### 2. Funções principais
- `infoRelator()`: Preenche a struct Relator com informações do usuário.
- `cadastrarRelatos()`: Preenche uma lista de relatos com dados informados pelo usuário.
- `verificarRaio()`: Verifica se o relato está a uma distância de até 10 km do relator usando a fórmula de Haversine.

## Cálculo da Distância com Haversine

### 3. Como calcular a distância entre dois pontos na Terra?
Utilizamos a fórmula de Haversine, que calcula a distância entre dois pontos na superfície terrestre a partir de suas latitudes e longitudes. A fórmula exige que as latitudes e longitudes sejam em radianos, por isso convertemos os dados informados pelo usuário em graus para radiano.

### Conversão de Graus para Radianos
Fórmula: `radianos = graus × π / 180`

### Etapas da fórmula de Haversine
1. Converta todas as latitudes e longitudes de graus para radianos.
2. Calcule as diferenças entre as latitudes e longitudes:
   - `dlat = lat2 - lat1`
   - `dlon = lon2 - lon1`
3. Aplique a fórmula:
   - `a = sin²(dlat/2) + cos(lat1) * cos(lat2) * sin²(dlon/2)`
4. Depois:
   - `c = 2 * atan2(√a, √(1−a))`
5. Finalmente:
   - `distância = R * c`

Onde:
- `R` = raio da Terra ≈ 6371 km.
- `sin` e `cos` → funções trigonométricas que operam com radianos.
- `atan2` → função que calcula arco-tangente, considerando o quadrante correto.

## Aplicação
Este sistema em C permite que usuários registrem seus dados pessoais e relatos de eventos catastróficos, informando a localização de cada relato por meio de coordenadas geográficas (latitude e longitude).
A principal funcionalidade é verificar se cada relato está dentro de um raio de 10 km em relação à localização do relator, utilizando a Fórmula de Haversine para calcular a distância entre os pontos na superfície terrestre.
Além disso, com seu menu funcional, o sistema coleta, armazena e processa as informações de forma estruturada, facilitando análises posteriores sobre a distribuição geográfica dos relatos.

