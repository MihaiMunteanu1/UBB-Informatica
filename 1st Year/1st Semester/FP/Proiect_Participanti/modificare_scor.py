
def sterge_scor(participanti, numar_participant):
    del participanti[numar_participant - 1]

def sterge_interval_scor_participanti(participanti, inceput, sfarsit):
    if 1 <= inceput <= sfarsit <= len(participanti):
        del participanti[inceput - 1:sfarsit]

def inlocuieste_scor(participanti, participant, scoruri_noi):
    if 1 <= participant <= len(participanti) and len(scoruri_noi) == 10:
        participanti[participant-1]["proba1"] = scoruri_noi[0]
        participanti[participant-1]["proba2"] = scoruri_noi[1]
        participanti[participant-1]["proba3"] = scoruri_noi[2]
        participanti[participant-1]["proba4"] = scoruri_noi[3]
        participanti[participant-1]["proba5"] = scoruri_noi[4]
        participanti[participant-1]["proba6"] = scoruri_noi[5]
        participanti[participant-1]["proba7"] = scoruri_noi[6]
        participanti[participant-1]["proba8"] = scoruri_noi[7]
        participanti[participant-1]["proba9"] = scoruri_noi[8]
        participanti[participant-1]["proba10"] = scoruri_noi[9]
    else:
        print("Participantul sau scorurile noi sunt invalide. Asigurați-vă că numărul participantului este valid și "
              "că ați introdus 10 scoruri noi.")
