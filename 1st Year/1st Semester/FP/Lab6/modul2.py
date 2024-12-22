participant=[]
def main2():
    global participant
    index=0
    optiune=input("Alegeti o optiune: ")
    optiune2=optiune.split(";")
    for i in range(len(optiune2)):
        optiune3=optiune2[i].split(" ")[0]
        if optiune3=="ADD":
            scoruri=optiune2[i].split(" ")
            scoruri.pop(0)
            if len(scoruri)!=10:
                print("Numar de scoruri invalid")
                break
            for j in range(10):
                if not 1<=int(scoruri[j])<=10:
                    print("Scoruri invalide")
                    break
            dictionar={"id_participant": index, "proba1": scoruri[0], "proba2": scoruri[1], "proba3": scoruri[2],
                 "proba4": scoruri[3], "proba5": scoruri[4], "proba6": scoruri[5], "proba7": scoruri[6],
                 "proba8": scoruri[7], "proba9": scoruri[8], "proba10": scoruri[9]}
            index=index+1
            participant.append(dictionar)
        if optiune3=="Filtreaza":
            scoruri=optiune2[i].split(" ")
            scoruri.pop(0)
            numar=int(scoruri[0])
            for ii in range(len(participant)):
                for j in range(1,11):
                    if participant[ii][f"proba{j}"] is not None:
                        scor=int(participant[ii][f"proba{j}"])
                        if scor % numar == 0:
                            participant[ii][f"proba{j}"] = None
        if optiune3=="Sterge":
            scoruri=optiune2[i].split(" ")
            scoruri.pop(0)
            nr=int(scoruri[0])
            if nr<=len(participant):
                del participant[nr-1]
                for j in range(nr-1,len(participant)):
                    participant[j]["id_participant"]=participant[j]["id_participant"]-1
            else:
                print("Nr participant invalid")
        if optiune3=="Inlocuieste":
            scoruri=optiune2[i].split(" ")
            scoruri.pop(0)
            id_p=int(scoruri[0])-1
            scoruri.pop(0)
            if scoruri:
                for j in range(10):
                    if not 1<=int(scoruri[j])<=10:
                        print("Scoruri invalide")
                        break
            if id_p+1<=len(participant):
                for j in range(10):
                    participant[id_p][f"proba{j+1}"]=scoruri[j]
            else:
                print("Participant invalid")
        if optiune3 == "Print":
            if participant:
                print(participant)
            else:
                print("nu exista participanti")
        if optiune3 == "Iesire":
            break