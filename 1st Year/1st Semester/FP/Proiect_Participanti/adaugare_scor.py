index = int(0)

def adauga_participant(participanti):
    global index
    scoruri = []
    for i in range(10):
        nota = int(input(f"Introduceți nota pentru proba {i + 1} (de la 1 la 10): "))
        if 1 <= nota <= 10:
            scoruri.append(nota)
        else:
            print("Scor invalid")
            return
    dictionar = {"id_participant": index, "proba1": scoruri[0], "proba2": scoruri[1], "proba3": scoruri[2],
                 "proba4": scoruri[3], "proba5": scoruri[4], "proba6": scoruri[5], "proba7": scoruri[6],
                 "proba8": scoruri[7], "proba9": scoruri[8], "proba10": scoruri[9]
                 }
    participanti.append(dictionar)
    index = index+1

def inserare_scor(participanti, nr_participant):
    ok = int(0)
    for i in range(10):
        if participanti[nr_participant - 1][f"proba{i+1}"] is None:
            ok = 1
    if ok:
        scor_nou = []
        for i in range(10):
            if participanti[nr_participant - 1][f"proba{i+1}"] is None:
                scor_proba = int(input(f"Introduceti scorul pentru proba {i+1}: "))
                if 0 < scor_proba < 11:
                    scor_nou.append(scor_proba)
                else:
                    print("Scor introdus invalid")
                    break
            else:
                scor_nou.append(participanti[nr_participant-1][f"proba{i+1}"])
        for i in range(10):
            participanti[nr_participant-1][f"proba{i+1}"] = scor_nou[i]
    else:
        print("Participantul are deja scor la toate probele")