class ValidatorLaborator:
    def valideaza_laborator(self,laborator):
        erori=""
        if laborator.get_numar_problema()<0:
            erori+="numar problema invalida\n"
        if laborator.get_descriere()=="":
            erori+="descriere invalida\n"
        if laborator.get_deadline()=="":
            erori+="data deadline invalida\n"
        if len(erori)>0:
            raise Exception(erori)