using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Configuration;

namespace LabSGBD
{
    public partial class Form1 : Form
    {
        static string connection = ConfigurationManager.ConnectionStrings["con"].ConnectionString;
        static string parentTableName = ConfigurationManager.AppSettings["parentTableName"];
        static string childTableName = ConfigurationManager.AppSettings["childTableName"];
        static int childNrOfCols = int.Parse(ConfigurationManager.AppSettings["childNrOfCols"]);
        static string insertQuery = ConfigurationManager.AppSettings["insertQuery"];
        static string updateQuery = ConfigurationManager.AppSettings["updateQuery"];
        static string deleteQuery = ConfigurationManager.AppSettings["deleteQuery"];
        static string selectQueryForParent = ConfigurationManager.AppSettings["selectQueryForParent"];
        static string selectQueryForChild = ConfigurationManager.AppSettings["selectQueryForChild"];
        static string childParameters = ConfigurationManager.AppSettings["childParameters"];
        static string childColumns = ConfigurationManager.AppSettings["childColumns"];
        static string childColumnsTypes = ConfigurationManager.AppSettings["childColumnsTypes"];
        static string parentToChildRelation = ConfigurationManager.AppSettings["parentToChildRelation"];
        static string childFkName = ConfigurationManager.AppSettings["childFK"];
        static string parentPkName = ConfigurationManager.AppSettings["parentPK"];
        static string childPkName = ConfigurationManager.AppSettings["childPK"];

        static string linkChildTableName = ConfigurationManager.AppSettings["linkChildTableName"] ?? string.Empty;
        static string deleteFromLinkTable = ConfigurationManager.AppSettings["deleteFromLinkTable"] ?? string.Empty;

        SqlConnection con = new SqlConnection(connection);
        SqlDataAdapter parentAdapter;
        SqlDataAdapter childAdapter;
        BindingSource childBindingSource = new BindingSource();
        BindingSource parentBindingSource = new BindingSource();
        DataSet dataSet = new DataSet();
        DataColumn childFKColumn;
        DataColumn parentPKColumn;
        DataRelation relation;

        static int selectedRowIndexParent;
        static int selectedRowIndexChild;

        TextBox[] textBoxes = new TextBox[childNrOfCols];
        Label[] labels = new Label[childNrOfCols];
        public Form1()
        {
            InitializeComponent();
            string[] names = childColumns.Split(',');
            for (int i = 0; i < childNrOfCols; i++)
            {
                labels[i] = new Label();
                textBoxes[i] = new TextBox();
                labels[i].Text = names[i];
                labels[i].Width = 80;
                labels[i].Font = new Font("Arial", 11);
      
                labels[i].Location = new Point(20 + i * 200, 20); 
                textBoxes[i].Text = "";
                textBoxes[i].Width = 80;
                textBoxes[i].Font = new Font("Arial", 11);
                textBoxes[i].Location = new Point(100 + i * 200, 20); 
            }

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.Width = 908;
            this.Height = 477;
            this.StartPosition = FormStartPosition.CenterScreen;

            for (int i = 0; i < childNrOfCols; i++)
            {
                this.Controls.Add(labels[i]);
                this.Controls.Add(textBoxes[i]);
            }
            try
            {
                con.Open();
                MessageBox.Show("Conexiune: " + con.State.ToString());

                parentAdapter = new SqlDataAdapter(selectQueryForParent, con);
                childAdapter = new SqlDataAdapter(selectQueryForChild, con);
                parentAdapter.Fill(dataSet, parentTableName);
                childAdapter.Fill(dataSet, childTableName);

                parentBindingSource.DataSource = dataSet.Tables[parentTableName];
                
                dataGridViewParent.DataSource = parentBindingSource;
                dataGridViewParent.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
                dataGridViewParent.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;

                parentPKColumn = dataSet.Tables[parentTableName].Columns[parentPkName];
                childFKColumn = dataSet.Tables[childTableName].Columns[childFkName];

                relation = new DataRelation(parentToChildRelation, parentPKColumn, childFKColumn);
                dataSet.Relations.Add(relation);

                childBindingSource.DataSource = parentBindingSource;
                childBindingSource.DataMember = parentToChildRelation;

                dataGridViewChild.DataSource = childBindingSource;
                dataGridViewChild.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.AllCells;
                dataGridViewChild.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
            }
            catch (SqlException err)
            {
                MessageBox.Show(err.Message.ToString());
            }
        }
        private void buttonAdd_Click(object sender, EventArgs e)
        {
            childAdapter.InsertCommand = new SqlCommand(insertQuery, con);

            string[] childparams = childParameters.Split(',');
            string[] childtypes = childColumnsTypes.Split(',');

            childAdapter.InsertCommand.Parameters.Add(childparams[1], SqlDbType.Int).Value = selectedRowIndexParent;

            try
            {
                for (int i = 0; i < childNrOfCols; i++)
                {
                    switch (childtypes[i])
                    {
                        case "string":
                            childAdapter.InsertCommand.Parameters
                                .Add(childparams[i + 2], SqlDbType.VarChar).Value = textBoxes[i].Text;
                            break;
                        case "int":
                            try
                            {
                                int value = int.Parse(textBoxes[i].Text);
                                childAdapter.InsertCommand.Parameters
                                    .Add(childparams[i + 2], SqlDbType.Int).Value = value;
                            }
                            catch (Exception)
                            {
                                MessageBox.Show("Not a valid number!");
                            }
                            break;
                        case "float":
                            try
                            {
                                float value= float.Parse(textBoxes[i].Text);
                                childAdapter.InsertCommand.Parameters
                                    .Add(childparams[i + 2], SqlDbType.Float).Value = value;
                            }
                            catch (Exception)
                            {
                                MessageBox.Show("Invalid float format!");
                            }
                            break;
                        default:
                            MessageBox.Show("Invalid data type!");
                            break;
                    }
                }
                childAdapter.InsertCommand.ExecuteNonQuery();
                dataSet.Clear();
                parentAdapter.Fill(dataSet, parentTableName);
                childAdapter.Fill(dataSet, childTableName);
                clearTextBoxes();

            }
            catch (SqlException ex)
            {
                MessageBox.Show("Error:\n" + ex.Message.ToString());
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            childAdapter.UpdateCommand = new SqlCommand(updateQuery, con);
            string[] childparams = childParameters.Split(',');
            string[] childtypes = childColumnsTypes.Split(',');
            try
            {
                for (int i = 0; i < childNrOfCols; i++)
                {
                    switch (childtypes[i])
                    {
                        case "string":
                            childAdapter.UpdateCommand.Parameters
                                .Add(childparams[i + 2], SqlDbType.VarChar).Value = textBoxes[i].Text;
                            break;
                        case "int":
                            try
                            {
                                int value = int.Parse(textBoxes[i].Text);
                                childAdapter.UpdateCommand.Parameters
                                    .Add(childparams[i + 2], SqlDbType.Int).Value = value;
                            }
                            catch (Exception)
                            {
                                MessageBox.Show("Not a valid number!");
                            }
                            break;
                        case "float":
                            try
                            {
                                float value = float.Parse(textBoxes[i].Text);
                                childAdapter.UpdateCommand.Parameters
                                    .Add(childparams[i + 2], SqlDbType.Float).Value = value;
                            }
                            catch (Exception)
                            {
                                MessageBox.Show("Invalid float format!");
                            }
                            break;
                        default:
                            MessageBox.Show("Invalid data type!");
                            break;
                    }
                }
                childAdapter.UpdateCommand.Parameters.Add(childparams[0], SqlDbType.Int).Value = selectedRowIndexChild;
                childAdapter.UpdateCommand.ExecuteNonQuery();
                dataSet.Clear();
                parentAdapter.Fill(dataSet, parentTableName);
                childAdapter.Fill(dataSet, childTableName);

                clearTextBoxes();

            }
            catch (SqlException ex)
            {
                MessageBox.Show("Error:\n" + ex.Message.ToString());
            }
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            childAdapter.DeleteCommand = new SqlCommand(deleteQuery, con);
            string[] childparams = childParameters.Split(',');

            if (linkChildTableName != string.Empty)
            {
                using (SqlCommand cmd = new SqlCommand(deleteFromLinkTable, con))
                    {
                        cmd.Parameters.AddWithValue("@childFk", selectedRowIndexChild);
                        cmd.ExecuteNonQuery();
                    }
            }
            

            try
            {
                childAdapter.DeleteCommand.Parameters.Add(childparams[0], SqlDbType.Int).Value = selectedRowIndexChild;
                childAdapter.DeleteCommand.ExecuteNonQuery();
                dataSet.Clear();

                parentAdapter.Fill(dataSet, parentTableName);
                childAdapter.Fill(dataSet, childTableName);

                clearTextBoxes();
            }
            catch (SqlException ex)
            {
                MessageBox.Show(ex.Message.ToString());
            }
        }

        private void dataGridViewParent_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            int rowIndex = e.RowIndex;
            if (rowIndex >= 0)
            {
                selectedRowIndexParent = int.Parse(dataGridViewParent.Rows[rowIndex].Cells[parentPkName].Value.ToString());

            }
        }

        private void dataGridViewChild_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            int rowIndex = e.RowIndex;
            if (rowIndex >= 0)
            {
                selectedRowIndexChild = int.Parse(dataGridViewChild.Rows[rowIndex].Cells[childPkName].Value.ToString());

            }
        }

        private void clearTextBoxes()
        {
            string[] names = childColumns.Split(',');
            for (int i = 0; i < childNrOfCols; i++)
            {
                textBoxes[i].Text = "";
            }
        }
    }
}
