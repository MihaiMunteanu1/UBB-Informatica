class ValidatorExamen:
    def valideaza_examen(self,examen):
        erori=""
        if examen.get_id()<0:
            erori+='id invalid\n'
        if examen.get_data()=="":
            erori+='data invalid\n'
        if examen.get_ora()=="":
            erori+='ora invalida\n'
        if examen.get_materia()=="":
            erori+='materie invalida\n'
        if examen.get_tip()!='normal' and examen.get_tip()!='restanta':
            erori+='tip invalid\n'
        if len(erori)>0:
            raise Exception(erori)