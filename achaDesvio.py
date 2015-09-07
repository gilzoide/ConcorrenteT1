import numpy
import sys

# arquivo a ser aberto é o do argumento
arq = open (sys.argv[1], 'r')

# pega a lista inteira de valores
lista = []
for linha in arq.readlines ():
    lista.append (float (linha))

# acha o desvio padrão do singlethread, que são os valores pares da lista
print 'Singlethreaded time standard deviation: ', numpy.std (lista[0::2])
# acha o desvio padrão do multithread, que são os valores ímpares da lista
print 'Multithreaded time standard deviation: ', numpy.std (lista[1::2])
