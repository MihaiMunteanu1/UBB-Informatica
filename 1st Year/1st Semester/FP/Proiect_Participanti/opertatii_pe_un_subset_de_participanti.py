def media_scoruri_interval_dat(participanti, nr_inceput, nr_sfarsit):
    suma = int(0)
    for i in range(10):
        for j in range(nr_inceput, nr_sfarsit + 1):
            suma += participanti[j - 1][f"proba{i+1}"]
    media = float(suma/(10*(nr_sfarsit-nr_inceput+1)))
    media = round(media, 2)
    return media

def scorul_minim_pentru_interval(participanti, nr_inceput, nr_sfarsit):
    minim = int(11)
    for i in range(10):
        for j in range(nr_inceput, nr_sfarsit+1):
            if participanti[j-1][f"proba{i+1}"] < minim:
                minim = participanti[j - 1][f"proba{i+1}"]
    return minim

def scor_multiplu_zece_interval_dat(participanti, nr_inceput, nr_sfarsit):
    concurenti_scor_zece = []
    for j in range(nr_inceput, nr_sfarsit+1):
        suma = int(0)
        for i in range(10):
            suma = suma+participanti[j-1][f"proba{i+1}"]
        if 0 == suma%10:
            concurenti_scor_zece.append(j)
    return concurenti_scor_zece