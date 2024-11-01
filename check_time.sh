#!/bin/bash

# Verifica se o comando foi passado como argumento
if [ "$#" -eq 0 ]; then
    echo "Uso: $0 <comando>"
    exit 1
fi

# Executa o comando e mede o tempo
start_time=$(date +%s.%N)  # Tempo de início em segundos com frações
"$@"                        # Executa o comando passado como argumento
end_time=$(date +%s.%N)    # Tempo de fim em segundos com frações

# Calcula o tempo total em segundos
elapsed_time=$(echo "$end_time - $start_time" | bc)

# Exibe o tempo total
echo "O comando levou $elapsed_time segundos para ser executado."

