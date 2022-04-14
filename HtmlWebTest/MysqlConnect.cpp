//
// Created by yangfu on 2022/4/14.
//

#include "MysqlConnect.h"
map<string,string > users;

bool MysqlConnect::Init(MYSQL *mysql, const string &host, const string &user, const string &psaaworld,const string& database) {
    if(m_bInit){
        mysql_close(m_pMysql);
    }
    m_pMysql= mysql_init(mysql);
    if(!m_pMysql){
        cout<<"mysql init failure"<<endl;
        return false;
    }
    MYSQL* pMysql=NULL;
    pMysql= mysql_real_connect(m_pMysql,host.c_str(),user.c_str(),psaaworld.c_str(),
                               database.c_str(),0,NULL,0);
    if (pMysql==m_pMysql){
        cout << "connect successful"<<endl;
       // mysql_query(pMysql,"set names utf8");
       return true;
    }    else{
        cout << "connect failure" <<endl;
        return false;
    }

}

bool MysqlConnect::QuerySql(const char *sql) {
    int ret=0;
    int len=strlen(sql);
    ret= mysql_real_query(m_pMysql,sql,len);
    if(ret){
        cout<< "Query failure"<<endl;
        return false;
    }
    m_pMysqlRes= mysql_store_result(m_pMysql);
    if(!m_pMysqlRes){
        cout << "res is null"<<endl;
        return false;
    }
    m_pMysqlField= mysql_fetch_field(m_pMysqlRes);
    int num_fields= mysql_num_fields(m_pMysqlRes);
    while(m_row= mysql_fetch_row(m_pMysqlRes)){
        string temp1(m_row[0]);
        string temp2(m_row[1]);
        cout << m_row[0]<<"   "<<m_row[1]<<endl;
        users[temp1]=temp2;
    }
    mysql_free_result(m_pMysqlRes);
}
MysqlConnect::MysqlConnect() {
    m_pMysql=NULL;
    m_pMysqlRes=NULL;
    m_pMysqlField=NULL;
    m_bInit= false;
}
MysqlConnect::~MysqlConnect() {
    if(m_pMysql!=NULL){
        if(m_bInit){
            mysql_close(m_pMysql);
        }
    }
}