from domain.examen import Examen
import datetime
class ServiceExamen:
    def __init__(self,repo_examen,valid_examen):
        self.__repo_examen=repo_examen
        self.__valid_examen=valid_examen

    def add_examen(self,id,data,ora,materie,tip):
        examen=Examen(id,data,ora,materie,tip)
        self.__valid_examen.valideaza_examen(examen)
        self.__repo_examen.add_examen(examen)
    def examene_de_maine(self):
        examene = self.__repo_examen.get_all()
        examene.sort(key=lambda x: x.get_ora())
        data_azi = str(datetime.date.today())
        data_int = int(data_azi[8:])
        data_int = data_int + 1
        data_maine = str(data_int) + '.' + data_azi[5:7]
        final_result = [examen for examen in examene if examen.get_data() == data_maine]
        return final_result

    def export(self,materia):
        result=[]
        toate_examene=self.__repo_examen.get_all()
        for examen in toate_examene:
            if examen.get_materia()==materia:
                result.append(examen)
        result.sort(key=lambda x:(x.get_data(),x.get_ora()))
        return result
    def examene_de_la_data(self,data):
        result_final=[]
        toate_examene=self.__repo_examen.get_all()
        for examen in toate_examene:
            data_examen=int(examen.get_data()[:2])
            if data_examen-data<=3:
                result_final.append(examen)
        return result_final

    def get_all(self):
        return self.__repo_examen.get_all()