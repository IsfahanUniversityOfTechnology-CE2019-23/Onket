
#include "good.h"

Question &Good::getQuestionPrivate(const QString &question_id)
{
    auto it=this->questions_id.find(question_id);
    //if this question id not found
    if(it == this->questions_id.end())
    {
        return (*this->questions.end());
    }
    ////if question id found
    else
    {
       for(auto it= this->questions.begin(); it != this->questions.end();it++)
       {
           if((*it).getId() == question_id)
           {
               return (*it);
           }
       }
    }
}

QString Good::toQString(unsigned int input)
{
    QString temp=QString::number(input);
    int size=temp.size();
    QString res=QString::number(size);
    res.append(temp);
    return  res;
}



void Good::setPrice(unsigned int  price)
{
    this->price=price;
}

void Good::setFinalPrice(unsigned int final_price)
{
    if(final_price>this->price)
    {
        this->price=final_price;
        this->discount_percent=0.0;
    }
    else
    {
        this->discount_percent=1.0-( long double)(final_price)/(long double)(this->price);
    }
}

bool Good::setDiscountPercent(double discount_percent)
{
    if(discount_percent < 1.0 && discount_percent >=0)
    {
        this->discount_percent=discount_percent;
    }
    return  false;
}

unsigned int Good::getPrice()
{
    return this->price;
}

unsigned int Good::getFinalPrice()
{
    return this->price *(1.0-discount_percent);
}

double Good::getFinalDiscountPrice()
{
    return this->discount_percent;
}

bool Good::existProperty(const QString &property_name)const
{
    auto it=this->properties.find(property_name);
    if(it== this->properties.end())
    {

        return  false;
    }
    else
    {
        return true;
    }
}

bool Good::addProperty(const QString &property_name)
{
    if(this->existProperty(property_name)==true)
    {
        return  false;
    }
    else
    {
        this->properties.insert(property_name,"");
        return  true;
    }
}

bool Good::setPropertyValue(const QString &property_name, const QString &property_value)
{
    if(this->existProperty(property_name)==false)
    {
        return false;
    }
    else
    {
        if(csv_validator::isValidInCsv(property_name)==false)
        {
            return false;
        }
        this->properties[property_name]=property_value;
        return true;

    }
}

QString Good::getPropertyValue(const QString &property_name)const
{
    if(this->existProperty(property_name)==false)
    {
        return "";
    }
    else
    {
        auto it=this->properties.find(property_name);
        return it.value();
    }
}

void Good::setPropertySeekBegin() const
{
    this->property_it=this->properties.begin();
}

QString Good::readPropertyName() const
{
   if(this->property_it!=this->properties.end())
   {
      QString res=property_it.key();
      property_it++;
      return res;
   }
   else
   {
       return "";
   }
}

bool Good::propertySeekAtEnd() const
{
    if(this->property_it==this->properties.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Good::existCommentSender(const QString &sender_id)
{
    auto it=this->comments_id.find(sender_id);
    if(it == comments_id.cend())
    {
        return  false;
    }
    else return  true;
}

 Comment &Good::getComment(const QString &sender_id)
{
    if(this->existCommentSender(sender_id) == false)
    {
        auto it=this->comments.end();
        return (*it);
    }
    else
    {
      auto it=this->comments.begin();
      for(;it != comments.end();it++)
      {
          if((*it).getSenderId()== sender_id)
              break;
      }
      return (*it);
    }
 }

 Comment &Good::readComment()
 {
     if(this->comments.isEmpty()==true || this->comments_it==this->comments.begin())
     {

         return this->comments.end().value();
     }

     else
     {
         this->comments_it--;
         return this->comments_it.value();
     }

 }

 void Good::setCommentSeekBegin()
 {
     this->comments_it=this->comments.end();
 }

 bool Good::commentSeekAtEnd()
 {
     if(this->comments_it == this->comments.begin()|| this->comments.isEmpty())
         return true;
     else
         return false;
 }

bool Good::addComment(const Comment &new_comment)
{
    if(this->existCommentSender(new_comment.getSenderId()) == true)
    {
        return  false;
    }
    else
    {
        this->comments_id.insert(new_comment.getSenderId(),true);
        if(this->comments_sort_by == "date")
        {
            this->comments.insert(file_QDate::toQString( new_comment.getDateCreate()),new_comment);
        }
        else if(this->comments_sort_by== "like_number")
        {
          this->comments.insert(Good::toQString(new_comment.getLikeNumber()),new_comment);
        }
        else if(this->comments_sort_by == "view_number")
        {
            this->comments.insert( Good::toQString(new_comment.getViewNumber()),new_comment);

        }
        else;
        return  true;
    }
}

bool Good::changeComment(const Comment &input_comment)
{
     if(this->existCommentSender(input_comment.getSenderId()) == false)
         return  false;
     else
     {
         for(auto it=this->comments.begin(); it!= this->comments.end(); it++)
         {
             if((*it).getSenderId() == input_comment.getSenderId())
             {
                (*it)=input_comment;
                 return  true;
             }
         }



         return  true;
     }
}

bool Good::existQuestionContent(const QString &content)
{
    for(auto it = this->questions.begin(); it != this->questions.end();it++)
    {
        if((*it).getContent()==content)
        {
            return  true;
        }
    }
    return  false;

}

bool Good::existQuestionId(const QString &question_id)
{
 auto it=this->questions_id.find(question_id);
 if(it == this->questions_id.end())
     return false;
 else
     return true;
}

QString Good::getIdQustion(const QString &content)
{
    if(this->existQuestionId(content) == false)
    {
        return "";
    }
    else
    {
        for(auto it = this->questions.begin(); it != this->questions.end();it++)
        {
            if((*it).getContent()==content)
            {
                return  (*it).getId();
            }
        }

        return  "";
    }
}

const Question &Good::getQuestion(const QString &question_id)
{
    auto it=this->questions_id.find(question_id);
    //if this question id not found
    if(it == this->questions_id.end())
    {
        return (*this->questions.end());
    }
    ////if question id found
    else
    {
       for(auto it= this->questions.begin(); it != this->questions.end();it++)
       {
           if((*it).getId() == question_id)
           {
               return (*it);
           }
       }
    }
}

const Question &Good::readQuestion()
{
  if(this->questions.isEmpty()==true || this->question_it== this->questions.begin())
  {
      return this->questions.end().value();
  }
  else
  {
      this->question_it--;
      return question_it.value();
  }
}

void Good::setQuestionSeekBegin()
{
    this->question_it=this->questions.end();
}

bool Good::QuestionSeekAtEnd()
{
    if(this->questions.isEmpty()==true ||this->question_it == this->questions.begin())
    {
        return true;
    }
    else
    {
        return false;
    }

}

//bool Good::existQuestion(const QString &question_id)
//{
//    auto it=this->questions_id.find(question_id);

//    if(it == this->questions_id.cend())
//    {
//        return  false;
//    }
//    else
//    {
//        return  true;
//    }
//}

//const Question &Good::getQuestion(const QString &question_id)
//{
//    if(this->existQuestion(question_id) == false)
//    {
//        auto it=this->questions.end();
//        return (*it);

//    }
//    else
//    {
//        auto it=this->questions.begin();
//        for(;it != this->questions.end(); it++)
//        {
//            if((*it).getId()== question_id)
//            {
//                break;
//            }
//        }
//        return (*it);
//    }

//}

QString Good::addQuestion(const QDate &date_create, const QString &sender_id, const QString &content)
{
    if(this->existQuestionContent(content)== true)
    {
        return "";
    }
    QString id="question";
    id.append(QString::number(this->questions.size()+1));


    Question q(date_create,id,sender_id,content);

    if(this->question_sort_by== "date")
    {
        this->questions.insert(file_QDate::toQString(q.getDateCreate()),q);
    }
    else if(this->question_sort_by== "reply_number")
    {
        this->questions.insert(Good::toQString(q.getReplyNumber()),q);
    }
    else;

    this->questions_id.insert(q.getId(),true);



    return  q.getId();

}

const Reply &Good::getReply(const QString &reply_id)
{
    auto it=this->replys.find(reply_id);

    return it.value();
}

Reply &Good::getReplyPrivate(const QString &reply_id)
{
    auto it=this->replys.find(reply_id);

    return it.value();
}

bool Good::existReply(const QString &sender_id, const QString &question_id)
{

    auto it=this->questions_id.find(question_id);
    if(it == this->questions_id.end())
    {
        return false;
    }
    else
    {
     const Question* q=& (this->getQuestion(question_id));

      for(q->setReplySeekBegin();q->replySeekAtEnd()==false;)
      {
          if(this->getReply(q->readReply()).getSenderId()  == sender_id)
          {
              return true;
          }



       }
      return false;
    }


}

bool Good::existReply(const QString &reply_id)
{
 auto it=this->replys.find(reply_id);
 if(it == this->replys.end())
     return false;
 else
     return true;
}

QString Good::addReply(const QString &question_id, const QDate &date_create, const QString &sender_id, const QString &content)
{

    if(this->existQuestionId(question_id)==false || this->existReply(sender_id,question_id)==true)
    {
        return "";
    }
    else
    {
        QString id="reply";
        id.append(QString::number(this->replys.size()+1));

        Reply r(date_create,id,sender_id,question_id,content);

        this->replys.insert(r.getId(),r);
        this->getQuestionPrivate(question_id).addReply(r.getId());

        return r.getId();
    }
}

bool Good::addReplyLike(const QString &reply_id, const QString &sender_id)
{
    if(this->existReply(reply_id)==false)
    {
        return false;
    }
    else
    {

        Reply* r=&(this->getReplyPrivate(reply_id));
        r->addLike(sender_id);
        this->getQuestionPrivate(r->getQuestionId()).changeReplyLike(r->getId(),r->getLikeNumber());

        return true;
    }

}

bool Good::addReplyDisLike(const QString &reply_id, const QString &sender_id)
{
    if(this->existReply(reply_id)==false)
    {
        return false;
    }
    else
    {

        Reply* r=&(this->getReplyPrivate(reply_id));
        r->addDisLike(sender_id);
        this->getQuestionPrivate(r->getQuestionId()).changeReplyLike(r->getId(),r->getLikeNumber());

        return true;

    }

}



void Good::commentSortByDate()
{
    if(this->comments_sort_by=="date")
    {
        return;
    }
    QMultiMap<QString,Comment> temp;
    for(auto it=this->comments.begin(); it!=this->comments.end();it++)
    {
        temp.insert(file_QDate::toQString((*it).getDateCreate()),(*it));

    }
    this->comments=temp;
    this->comments_sort_by="date";
    this->setCommentSeekBegin();
}

void Good::commentSortByLike()
{
    if(this->comments_sort_by=="like_number")
    {
        return;
    }
   QMultiMap<QString,Comment>temp;
   for(auto it=this->comments.begin(); it!= this->comments.end();it++)
   {
       temp.insert(Good::toQString((*it).getLikeNumber()),(*it));
   }
   this->comments=temp;
   this->comments_sort_by="like_number";
   this->setCommentSeekBegin();
}

void Good::commentSortByView()
{
    if(this->comments_sort_by=="view_number")
    {
        return;
    }
   QMultiMap<QString,Comment>temp;
   for(auto it=this->comments.begin(); it!= this->comments.end();it++)
   {
       temp.insert(Good::toQString((*it).getViewNumber()),(*it));
   }
   this->comments=temp;
   this->comments_sort_by="view_number";
   this->setCommentSeekBegin();
}

void Good::QuestionSortByDate()
{
    if(this->question_sort_by== "date")
    {
        return;
    }
    QMultiMap<QString,Question>temp;
    for(auto it=this->questions.begin(); it!= this->questions.end();it++)
    {
        temp.insert(file_QDate::toQString((*it).getDateCreate()),(*it));

    }
    this->questions=temp;

    this->question_sort_by="date";

}

void Good::QuestionSortyByReplyNumber()
{
    if(this->question_sort_by== "reply_number")
    {
        return;
    }
    QMultiMap<QString,Question>temp;
    for(auto it=this->questions.begin();it != this->questions.end();it++)
    {
        temp.insert(Good::toQString((*it).getReplyNumber()),*it);
    }
    this->questions=temp;
    this->question_sort_by="reply_number";
}

void Good::commentsReadFile()
{
    this->commentSortByDate();
    QString path="D:/HelpMemory/OnketFile";
    path.append("/Comments/");
    QDir d(path);
    if(d.exists()==false)
    {
        d.mkdir(path);
    }
    path.append(this->id);
    path.append(".xml");
    QFile file(path);

    if(file.open(QFile::ReadOnly | QFile::Text)==true)
    {
        QXmlStreamReader xml_reader;
        xml_reader.setDevice(& file);
        QString sender_id,advantages,disadvantages,description;
        QMap<QString,double> items;
        QMap<QString,bool> user_like;
        QDate date_create;
       while(xml_reader.atEnd()==false)
       {

          if(xml_reader.isStartElement()==true)
          {

             if(xml_reader.name()=="sender_id")
             {
               sender_id=xml_reader.readElementText();

             }
             else if(xml_reader.name()=="date")
             {
                 date_create=file_QDate::toQDate(xml_reader.readElementText());


             }
             else if(xml_reader.name()=="advantages")
             {
                 advantages=xml_reader.readElementText();


             }
             else if(xml_reader.name()=="disadvantages")
             {
                 disadvantages=xml_reader.readElementText();


             }
             else if(xml_reader.name()=="description")
             {
               description=xml_reader.readElementText();

             }
             else if(xml_reader.name()=="items")
             {
                items=xml_QMap::toDoubleQMap(xml_reader.readElementText());

             }
             else if(xml_reader.name()=="users_like")
             {
                 user_like=xml_QMap::toBoolQMap(xml_reader.readElementText());
                 Comment c(date_create,sender_id,advantages,disadvantages,description);

                 this->addComment(c);

                 for(auto it=items.cbegin();it != items.cend();it++)
                 {
                     this->getComment(c.getSenderId()).insertItem(it.key());
                     this->getComment(c.getSenderId()).setItemValue(it.key(),it.value());
                 }

                 for(auto it=user_like.cbegin();it != user_like.cend();it++)
                 {
                     if(it.value()==true)
                     {
                         this->getComment(c.getSenderId()).addLike(it.key());

                     }
                     else
                     {
                          this->getComment(c.getSenderId()).addDisLike(it.key());
                     }
                 }


             }
             else;






       }
        xml_reader.readNext();
    }
    file.flush();
    file.close();
   }
}

void Good::commentsWriteToFile()
{
    this->commentSortByDate();
    QString path="D:/HelpMemory/OnketFile";
    path.append("/Comments/");
    QDir d(path);
    if(d.exists()==false)
    {
        d.mkdir(path);
    }
    path.append(this->id);
    path.append(".xml");
    QFile file(path);

    if(file.open(QFile::WriteOnly | QFile::Text)== true)
    {
        QXmlStreamWriter xml_writer;
        xml_writer.setDevice(& file);
        xml_writer.setAutoFormatting(true);
        xml_writer.writeStartDocument();
        xml_writer.writeStartElement("comment_list");

        for(auto it=this->comments.begin();it != this->comments.end();it++)
        {
            (*it).addToFile(xml_writer);
        }
        xml_writer.writeEndElement();
        xml_writer.writeEndDocument();

        file.flush();
        file.close();
    }


    if(this->comments_sort_by=="like_number")
    {
        this->commentSortByLike();
    }
    else if(this->comments_sort_by=="veiw_number")
    {
        this->commentSortByView();
    }
    else;
    
}

void Good::QuestionReadFile()
{
   QString path="d:/HelpMemory/OnketFile/Questions/";path.append(this->id);path.append(".xml");
   QFile file(path);
   if(file.open(QFile::ReadOnly| QFile::Text)==true)
   {
       QXmlStreamReader xml_reader;
       xml_reader.setDevice(& file);
       QString id, sender_id,content;
       QDate date_creat;
       for(;xml_reader.atEnd()==false;xml_reader.readNext())
       {
           if(xml_reader.isStartElement())
           {
               if(xml_reader.name()=="id")
               {
                   id=xml_reader.readElementText();
               }
               else if(xml_reader.name()=="sender_id")
               {
                   sender_id=xml_reader.readElementText();
               }
               else if(xml_reader.name()=="date")
               {
                   date_creat=file_QDate::toQDate(xml_reader.readElementText());
               }

               else if(xml_reader.name()=="content")
               {
                   content=xml_reader.readElementText();
                   Question q(date_creat,id,sender_id,content);
                   this->questions.insert(file_QDate::toQString(date_creat),q);
                   this->questions_id.insert(id,true);
               }


           }
       }
       file.flush();
       file.close();
   }
}

void Good::QUestionWriteToFile()
{
    QString path="d:/HelpMemory/OnketFile";
    QDir d(path);
    if(d.exists("Questions")==false)
    {
        d.mkdir("Questions");
    }
    path.append("/Questions");path.append("/");path.append(this->id);path.append(".xml");
    QFile file(path);
    if(file.open(QFile::WriteOnly | QFile::Text)==true)
    {
        this->QuestionSortByDate();
        QXmlStreamWriter xml_writer;
        xml_writer.setDevice(& file);
        xml_writer.setAutoFormatting(true);
        xml_writer.writeStartDocument();
        xml_writer.writeStartElement("Question_list");

        for(auto it=this->questions.begin();it != this->questions.end();it++)
        {
            it.value().addToFile(xml_writer);
        }

        xml_writer.writeEndElement();
        xml_writer.writeEndDocument();

        file.flush();
        file.close();
        if(this->question_sort_by=="reply_number")
        {
            this->QuestionSortyByReplyNumber();
        }

    }
 

}

void Good::ReplyReadFile()
{
    QString path="d:/HelpMemory/OnketFile/Reply/";path.append(this->id);path.append(".xml");
    QFile file(path);
    if(file.open(QFile::ReadOnly | QFile::Text)==true)
    {
        QXmlStreamReader xml_reader;
        xml_reader.setDevice(& file);

        QString id,question_id,sender_id,content;
        QDate date_creat;
        QMap<QString,bool> users_like;

        for(;xml_reader.atEnd()==false;xml_reader.readNext())
        {
            if(xml_reader.isStartElement()==true)
            {
                if(xml_reader.name()=="id")
                {
                    id=xml_reader.readElementText();
                }
               else if(xml_reader.name()=="sender_id")
                {
                    sender_id=xml_reader.readElementText();
                }
                else if(xml_reader.name()=="question_id")
                 {
                     question_id=xml_reader.readElementText();
                 }
                else if(xml_reader.name()=="date")
                 {
                     date_creat=file_QDate::toQDate(xml_reader.readElementText());
                 }
                else if(xml_reader.name()=="content")
                 {
                     content=xml_reader.readElementText();
                 }
                else if(xml_reader.name()=="users_like")
                 {
                      users_like=xml_QMap::toBoolQMap(xml_reader.readElementText());


                     if(this->existQuestionId(question_id)==true)
                     {
                         Reply r(date_creat,id,sender_id,question_id,content);
                         this->replys.insert(r.getId(),r);
                         this->getQuestionPrivate(r.getQuestionId()).addReply(r.getId());

                         for(auto it=users_like.begin();it != users_like.end();it++)
                         {
                             if(it.value()==true)
                             {
                                 this->addReplyLike(r.getId(),r.getSenderId());
                             }
                             else
                             {
                                 this->addReplyDisLike(r.getId(),r.getSenderId());
                             }
                         }
                     }
                     else;



                 }


            }
        }
        file.close();
        file.flush();
    }
}

void Good::ReplyWriteToFile()
{
    QString path="d:/HelpMemory/OnketFile";
    QDir d(path);
    if(d.exists("Reply")==false)
    {
        d.mkdir("Reply");
    }
    path.append("/Reply");path.append("/");path.append(this->id);path.append(".xml");
    QFile file(path);
    if(file.open(QFile::WriteOnly | QFile::Text)==true)
    {

        QXmlStreamWriter xml_writer;
        xml_writer.setDevice(& file);
        xml_writer.setAutoFormatting(true);
        xml_writer.writeStartDocument();
        xml_writer.writeStartElement("Reply_list");

        for(auto it=this->replys.begin();it != this->replys.end();it++)
        {
            it.value().addToFile(xml_writer);
        }

        xml_writer.writeEndElement();
        xml_writer.writeEndDocument();

        file.flush();
        file.close();

    }


}





Good::Good()

{


}


