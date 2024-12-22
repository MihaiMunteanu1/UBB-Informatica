class ValidatorNota:

    def validare_nota(self,nota):
        erori=""
        if 0.0>=nota.get_nota() or nota.get_nota()>10.0:
            erori+="nota invalida!"
        if len(erori)>0:
            raise Exception(erori)