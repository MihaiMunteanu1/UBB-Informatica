class ValidatorNota:
    def validare_nota(self,nota):
        erori=""
        if 0>=nota.get_val_nota() or nota.get_val_nota()>10:
            erori+="nota invalida\n"
        if len(erori)>0:
            raise Exception(erori)