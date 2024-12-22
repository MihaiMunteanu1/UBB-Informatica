
def filtrare_participanti_scor_multiplu_nr(participanti, numar_dat):
    for i in range(len(participanti)):
        for j in range(10):
            if participanti[i][f"proba{j+1}"] is not None:
                if participanti[i][f"proba{j+1}"] % numar_dat == 0:
                    participanti[i][f"proba{j+1}"] = None
    return participanti

def filtrare_participanti_scor_mic_decat_scor_dat(participanti, numar1_dat):
    for i in range(len(participanti)):
        for j in range(10):
            if participanti[i][f"proba{j+1}"] is not None:
                if participanti[i][f"proba{j+1}"] < numar1_dat:
                    participanti[i][f"proba{j+1}"] = None
    return participanti