class ValidatorPiesa:
    def valideaza_piesa(self,piesa):
        erori=""
        if piesa.get_id()<0:
            erori+='id invalid\n'
        if piesa.get_titlu()=="":
            erori+='titilu nevid\n'
        if piesa.get_regizor()=="":
            erori+='regizor nevid\n'
        if piesa.get_gen()!='Comedie' and piesa.get_gen()!='Drama' and piesa.get_gen()!='Satira' and piesa.get_gen()!='Altele':
            erori+='gen invalid\n'
        if piesa.get_durata()<0:
            erori+='durata invalida\n'
        if len(erori)>0:
            raise Exception(erori)
    def valideaza_piesa2(self,titlu,regizor,gen,durata):
        erori = ""
        if titlu == "":
            erori += 'titilu nevid\n'
        if regizor == "":
            erori += 'regizor nevid\n'
        if gen != 'Comedie' and gen != 'Drama' and gen != 'Satira' and gen != 'Altele':
            erori += 'gen invalid\n'
        if durata < 0:
            erori += 'durata invalida\n'
        if len(erori) > 0:
            raise Exception(erori)