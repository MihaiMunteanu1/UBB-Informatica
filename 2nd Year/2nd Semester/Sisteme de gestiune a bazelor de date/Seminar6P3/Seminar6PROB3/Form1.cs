using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Seminar6PROB3
{
    public partial class Form1 : Form
    {
        string conS = @"Server=MIHAIMUNTEANU\SQLEXPRESS;Database=Problema3;Integrated Security=true;
        TrustServerCertificate=true;";
        DataSet ds = new DataSet(); // tine minte tabelele in memorie
        SqlDataAdapter childAdapter = new SqlDataAdapter(); // intermediar inter baza de date si DataSet
        SqlDataAdapter parentAdapter = new SqlDataAdapter(); // aduc datele din tabele SQL in dataset
        BindingSource bsParent = new BindingSource(); // legatura intre date si controale
        BindingSource bsChild = new BindingSource(); // legatura intre DataSet si DataGridView

        int childSelected = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    parentAdapter.SelectCommand = new SqlCommand("SELECT * FROM Producatori;", con);
                    childAdapter.SelectCommand = new SqlCommand("SELECT * FROM Biscuiti;", con);
                    parentAdapter.Fill(ds, "Producatori");
                    childAdapter.Fill(ds, "Biscuiti");
                    DataColumn pkColumn = ds.Tables["Producatori"].Columns["cod_p"];
                    DataColumn fkColumn = ds.Tables["Biscuiti"].Columns["cod_p"];
                    DataRelation relation = new DataRelation("fk_parent_child", pkColumn, fkColumn);
                    ds.Relations.Add(relation);
                    bsParent.DataSource = ds.Tables["Producatori"];
                    dataGridViewParent.DataSource = bsParent;
                    bsChild.DataSource = bsParent;
                    bsChild.DataMember = "fk_parent_child";
                    dataGridViewChild.DataSource = bsChild;
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            if (textBoxCod.Text == "")
            {
                MessageBox.Show("Selectati un producator penta adauga un  biscuit!");
                return;
            }
            if (textBoxNume.Text == "" || textBoxCalorii.Text == "" || textBoxPret.Text == "")
            {
                MessageBox.Show("Complete all the fields!");
                return;
            }

            string nume = textBoxNume.Text.Trim();
            double pret = double.Parse(textBoxPret.Text.Trim());
            int calorii= int.Parse(textBoxCalorii.Text.Trim());
            
            int cod_p = int.Parse(textBoxCod.Text.Trim());


            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    using (SqlCommand cmd = new SqlCommand(@"INSERT INTO Biscuiti (nume_b,nr_calorii ,pret, cod_p)
                                                     VALUES (@nume, @calorii, @pret, @cod_p)", con))
                    {
                        cmd.Parameters.AddWithValue("@nume", nume);
                        cmd.Parameters.AddWithValue("@calorii", calorii);
                        cmd.Parameters.AddWithValue("@pret", pret);
                        cmd.Parameters.AddWithValue("@cod_p", cod_p);

                        cmd.ExecuteNonQuery();
                    }
                }

                MessageBox.Show("Biscuit adaugat!");
                Reload();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare la adaugare: " + ex.Message);
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            if (childSelected == -1)
            {
                MessageBox.Show("Selectati un biscuit pentru modificare!");
                return;
            }

            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    using (SqlCommand cmd = new SqlCommand(@"UPDATE Biscuiti 
                                                         SET nume_b = @nume, 
                                                         nr_calorii = @calorii, 
                                                         pret = @pret, 
                                                         cod_p = @cod_p WHERE cod_b = @id", con))
                    {
                        cmd.Parameters.AddWithValue("@nume", textBoxNume.Text);
                        cmd.Parameters.AddWithValue("@calorii", textBoxCalorii.Text);
                        cmd.Parameters.AddWithValue("@pret", textBoxPret.Text);
                        cmd.Parameters.AddWithValue("@cod_p", textBoxCod.Text);
                        cmd.Parameters.AddWithValue("@id", childSelected);

                        cmd.ExecuteNonQuery();
                    }
                }
                MessageBox.Show("Date actualizate cu succes!");
                Reload();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare: " + ex.Message);
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            if (childSelected == -1)
            {
                MessageBox.Show("Selectati un biscuit!");
                return;
            }
            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    con.Open();
                    using (SqlCommand cmd = new SqlCommand("DELETE FROM Biscuiti WHERE cod_b = @id", con))
                    {
                        cmd.Parameters.AddWithValue("@id", childSelected);
                        cmd.ExecuteNonQuery();
                    }
                }
                MessageBox.Show("Biscuit sters!");
                Reload();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Eroare: " + ex.Message);
            }
        }
        

        private void dataGridViewChild_RowEnter(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex > -1)
            {
                DataGridViewRow row = dataGridViewChild.Rows[e.RowIndex];
                childSelected = Convert.ToInt32(row.Cells["cod_b"].Value); // id - child table

                textBoxNume.Text = row.Cells["nume_b"].Value.ToString();
                textBoxCalorii.Text = row.Cells["nr_calorii"].Value.ToString();
                textBoxPret.Text = row.Cells["pret"].Value.ToString();
                textBoxCod.Text = row.Cells["cod_p"].Value.ToString();

            }
        }
        private void Reload()
        {

            try
            {
                using (SqlConnection con = new SqlConnection(conS))
                {
                    /* daca folosim doar SqlDataAdapters, putem omite deschiderea explicita a conexiunii, 
                     * deoarece SqlDataAdapters deschid si inchid automat conexiunea atunci cand este 
                     * apelata metoda Fill()
                     */
                    parentAdapter.SelectCommand.Connection = con;
                    childAdapter.SelectCommand.Connection = con;
                    if (ds.Tables.Contains("Biscuiti"))
                    {
                        ds.Tables["Biscuiti"].Clear();

                    }
                    if (ds.Tables.Contains("Producatori"))
                    {
                        ds.Tables["Producatori"].Clear();
                    }
                    parentAdapter.Fill(ds, "Producatori");
                    childAdapter.Fill(ds, "Biscuiti");

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }
    }
}
