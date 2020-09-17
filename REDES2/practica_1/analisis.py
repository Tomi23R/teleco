if __name__ == "__main__":
	i = 0
	f = open("salidaX7.txt", "r")
	palabras_intro = f.read().split("\n")
	escritura = open("final.txt", "w")
	result = True
	anterior = 0

	while(result is True):
		try:
			palabras = palabras_intro[i].split(" ")

			if(i == 0):
				tiempo = palabras[3]
				anterior = tiempo
				diferencia = 0
				tamanio = palabras[9]
				i += 1
			else:
				tiempo = palabras[3]
				diferencia = float(tiempo) - float(anterior)
				tamanio = palabras[9]
				anterior = tiempo
				i += 1
			escritura.write(str(tiempo) + ";" + str(diferencia) + ";" + str(tamanio) + "\n")
		except Exception as e:
			result = False

	f.close()
	escritura.close()




	
