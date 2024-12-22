class ValidatorTractor:
    def valideaza_tractor(self,tractor):
        """
        Functie care verifica daca datele tractorului sunt corecte
        :param tractor:
        :return:
        """
        erori=""
        if tractor.get_id()<0:
            erori+='id invalid\n'
        if tractor.get_denumire()=="":
            erori+='denumire invalida\n'
        if tractor.get_pret()<0:
            erori+='pret invalid\n'
        if tractor.get_model()=="":
            erori+='model invalid\n'
        if tractor.get_data()=="":
            erori+='data invalida\n'
        if len(erori)>0:
            raise Exception(erori)