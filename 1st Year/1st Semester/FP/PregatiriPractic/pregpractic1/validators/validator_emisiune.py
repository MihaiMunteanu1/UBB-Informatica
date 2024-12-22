class ValidatorEmisiune:
    def valideaza_emisiune(self,emisiune):
        erori=""
        if emisiune.get_id()<0:
            erori+='id invalid\n'
        if emisiune.get_nume()=="":
            erori+='nume invalid\n'
        if emisiune.get_tip()=="":
            erori+='tip invalid\n'
        if emisiune.get_durata()<0:
            erori+='durata invalida\n'
        if emisiune.get_descriere()=="":
            erori+='descriere invalida'
        if len(erori)>0:
            raise Exception(erori)