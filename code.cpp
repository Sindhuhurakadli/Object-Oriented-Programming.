#include <iostream>
#include <string>

using namespace std;

const int MAX_CART = 50;  
const int MAX_ORDER=30;

class Exception
{
    public:
    int err_id;
    string errmsg;
    Exception(){}
    Exception(int e,string m):err_id(e),errmsg(m){}
    void show()
    {
        cout<<err_id<<":"<<errmsg<<endl;
    }

};

class user
{
    protected:
    string name;
    string email;
    string password;
    string address;

    public:
    user(){}
    user(string n,string e,string p,string a):name(n),email(e),password(p),address(a){}
    virtual void login()
    {
        cout << name << " logged in" << endl;
    }

     virtual void logout() 
     {
        cout << name << " logged out" << endl;
     }

     void update_profile(string n, string e, string a)
     {
        name = n;
        email = e;
        address = a;
        cout << "Profile updated: " << name << ", " << email << ", " << address << endl;
     }

    void reset_password(string new_password)
     {
        password = new_password;
        cout << "Password reset successfully" << endl;
     }

};

class product
{
    public:
    int product_id;
    string name;
    double price;
    int stoke_quantity;

    public:
    product(){}
    product(int p,string n,double pt,int s):product_id(p),name(n),price(pt),stoke_quantity(s){}

    bool is_available()
    {
        return stoke_quantity>0;
    }

    void update_stokequantity(int new_quantity)
    {
        stoke_quantity=new_quantity;

    }

    int discount(double price)
    {
        if(price>10000)
        {
            int tot;
            tot=price-(price*0.15);
            return tot;

        }
        else
        {
            int tot;
            tot=price-(price*0.05);
            return tot;
        }
    }

    void printdetails()
    {
        cout<<product_id<<":"<<name<<":"<<price<<":"<<stoke_quantity<<endl;
    }


};

class seller:public user
{
    public:
    int sellerid;
    string store;
    float rating;
    product p[50];
    int p_count=0;

    seller(){}
    seller(string n, string e, string p, string a, int sid, string st, float r ):user(n,e,p,a),sellerid(sid),store(st),rating(r){}

    void login()
    {
        string p;
        cout<<"Enter passward"<<endl;
        cin>>p;
        if(p==password)
        {
            cout<<"Login successful"<<endl;
        }
        else{
        cout<<"login failed"<<endl;
        cout<<"Do u want to reset passward"<<endl;
        string choice;
        cin>>choice;
        if(choice=="yes")
        {
            cout<<"Enter new passward"<<endl;
            string n;
            cin>>n;
            reset_password(n);
        }
        }
    }

    void logout()
    {
       logout(); 
    }
    
    void addProduct(const product&pt)
    {
        if(p_count<50)
        {
            p[p_count++]=pt;
        }
        else
        {
            throw Exception(1001,"limit reached");
        }    
    }

    void deleteProduct(int pid)
    {
    for(int i=0;i<p_count;i++)
    {
        if(p[i].product_id==pid)
        {
           for(int j=i;j<p_count-1;++j)
           {
               p[j]=p[j+1];
           } 
           p_count--;
        }
    }
   }


 void list_product()
 {
   cout << "Products listed by "<< store << ": "<<endl;
    for (int i = 0; i <p_count; ++i) {
            p[i].printdetails();
        }
 }

};

class wishlist
{
    public:
    product p[50];
    int p_count=0;

    wishlist(){}
    

    void searchProduct(int pid)
    {
        for(int i=0;i<p_count;i++)
        {
            if(p[i].product_id==pid)
            {
                cout<<"Item found"<<endl;
                p[i].printdetails();
            }
            else
            {
                throw Exception(1002,"limit reached");
            }
        }
    }

    void addWishlist(const product &pt)
    {
       if(p_count<50)
       {
         p[p_count++]=pt;
       }
       else
       {
         throw Exception(1003,"You can't add wishlist,limit reached");
       }
    }


     void remove_wishlist(int pid)
    {
    for(int i=0;i<p_count;i++)
    {
        if(p[i].product_id==pid)
        {
           for(int j=i;j<p_count-1;++j)
           {
               p[j]=p[j+1];
           } 
           p_count--;
        }
    }
   }

   void display()
   {
     for(int i=0;i<p_count;i++)
     {
        p[i].printdetails();
     }
   }

};


class Cart
{
    public:
    int cart_id;
    int buyer_id;
    double tot=0;
    product p[50];
    int p_count=0;

    Cart(){};
    Cart(int c,int bid,double p):cart_id(c),buyer_id(bid),tot(p){};

    void addCart(const product &prod)
    {
        if(p_count<MAX_CART)
        {
            p[p_count++]=prod;
            tot+=prod.price;
        }
        else
        {
            throw Exception(1005,"limit reached you can't add to the cart");
        }
    }


     void removefrom_cart(int pid)
    {
    for(int i=0;i<p_count;i++)
    {
        if(p[i].product_id==pid)
        {
           for(int j=i;j<p_count-1;++j)
           {
               p[j]=p[j+1];
           } 
           p_count--;
        }
    }
   }

   void applyDiscount()
   {
    if(tot>=10000&&tot<20000)
    {
       tot=tot-(tot*0.25);
    }
    else
    {
        tot=tot-(tot*0.05);
    }
   }

   void displaydetails()
   {
     for(int i=0;i<p_count;i++)
     {
        p[i].printdetails();
        
     }
     cout<<"total price="<<tot<<endl;
   }

    void clear_cart() {
        p_count = 0;
        cout << "Cart cleared." << endl;
    }

};

class Order {
public:
    int order_id;
    string buyer_name;
    product products[MAX_CART];
    int product_count;
    double total_amount;

    Order(){}

    Order(int oid, string bname) : order_id(oid), buyer_name(bname), product_count(0), total_amount(0.0) {}

    void addProduct(const product &product) {
        if (product_count< MAX_CART) {
            products[product_count++] = product;
            total_amount+=product.price;
        }
        else
        {
            throw Exception(1006,"can't add products");
        }
    }

    void printOrderDetails() const {
        cout << "Order ID: " << order_id << endl;
        cout << "Buyer: " << buyer_name << endl;
        cout << "Products: " << endl;
        for (int i = 0; i < product_count; i++) {
            cout << "  - " << products[i].name << " ($" << products[i].price << ")" << endl;
        }
        cout << "Total Amount: $" << total_amount << endl;
    }
};

class Buyer:public user{
    public:
    int buyer_id;
    wishlist w;
    int w_count;
    Cart c;
    int num_cart;
    Order *orders;
    int o_count;


    public:
    Buyer():orders(new Order[MAX_ORDER]), o_count(0) {}
    Buyer(string n, string e, string p, string a, int bid):user( n, e, p, a), buyer_id(bid), num_cart(0),w_count(0), orders(new Order[MAX_ORDER]), o_count(0) {}

     void add_to_cart(product &pt) {
        c.addCart(pt);
       
    }

    ~Buyer() {
        delete[] orders;
    }
  
    void list_Wishlist(product &pt)
    {
       w.addWishlist(pt);
    }
    
     void remove_from_cart(int product_id) {
        c.removefrom_cart(product_id);
    }

       void place_order() {
        if (c.p_count == 0) {
            cout << "No products in cart to place an order." << endl;
            return;
        }

        static int next_oid = 0;
        Order new_order(next_oid++, name);

        for (int i=0; i<c.p_count; i++) {
            new_order.addProduct(c.p[i]);
        }

        orders[o_count++] = new_order;
        c.clear_cart();

        cout << "Order placed successfully!" << endl;
        new_order.printOrderDetails();
    }

    void view_order_status(int order_id)  {
        for (int i = 0; i < o_count; ++i) {
            if (orders[i].order_id == order_id) {
                orders[i].printOrderDetails();
                return;
            }
        }
        cout << "Order ID"<< order_id << "not found."<< endl;
    }

     void invoice() const {
        if (o_count == 0) {
            cout << "No orders placed yet." << endl;
            return;
        }
        for (int i = 0; i < o_count; ++i) {
            orders[i].printOrderDetails();
        }
    }

      void cancel_order(int order_id) {
        for (int i = 0; i < o_count; ++i) {
            if (orders[i].order_id == order_id) {
                for (int j = i; j < o_count - 1; ++j) {
                    orders[j] = orders[j + 1];
                }
                o_count--;
                cout <<"order id"<<order_id<<" is deleted" << endl;
                return;
            }
        }
    }

};

class Payment {
protected:
    int payment_id;
    Order* order;
    string payment_method;
    string status;

public:
    Payment(int id, Order* o, string method, string stat)
        : payment_id(id), order(o), payment_method(method), status(stat) {}

    virtual void refund_payment(int payment_id) = 0;
    virtual void update_payment_status(int payment_id, string status) = 0;
    virtual void get_payment_details(int payment_id) = 0;

};


class OnlinePayment : public Payment {
private:
    string type;

public:
    OnlinePayment(int id, Order* o, string method, string stat, string t) : Payment(id, o, method, stat), type(t) {}

    void refund_payment(int payment_id)
    {
        if (order->total_amount == 0)
            cout << "Online payment refunded for payment ID: "<< payment_id <<endl;
        else
           throw Exception(1007,"can't refund your amount");
    }

    void update_payment_status(int payment_id,string status)
    {
        
        cout << "Payment status updated for payment ID: " << payment_id << " to status " <<status <<endl;
    }

    void get_payment_details(int payment_id){
        cout << "Payment details for payment ID: " << payment_id << endl;
        cout << "Payment Method: " << payment_method << endl;
        cout << "Payment Status: " << status << endl;
        cout << "Payment Type: " << type << endl;
        order->printOrderDetails();
    }
};



class OfflinePayment : public Payment {
public:
    OfflinePayment(int id, Order* o, string method, string stat)
        : Payment(id, o, method, stat) {}

    void refund_payment(int payment_id) {
         if(order->total_amount==0)
        cout << "Offline payment refunded for payment ID: " << payment_id << endl;
        else
        throw Exception(1008,"cant refund your amount");
    }

    void update_payment_status(int pid, string s)  {
       payment_id=pid;
        status=s;
        cout << "Payment status updated for payment ID: " << payment_id <<"To status "<<status<< endl;
    }

    void get_payment_details(int payment_id){
    cout << "Payment details for payment ID: " << payment_id << endl;
    cout << "Payment Method: " << payment_method << endl; 
    cout << "Payment Status: " << status << endl;
    order->printOrderDetails();
}
};


class Review {
private:
    int review_id;
    product* p;
    int buyer_id;
    int rating;
    string comment;

public:
    Review(int rid, product * prod, int bid, int rt, string cm)
        : review_id(rid), p(prod), buyer_id(bid), rating(rt), comment(cm) {}

    void submit_review() {
        cout << "Review submitted for product: " << p->name << endl;
    }

    void update_review(int rid) {
        if (rid == review_id) 
        {
            cout << "Review updated for review ID: " << review_id << endl;
        } 
        else {
            throw Exception(1008,"can't update your review");
        }
    }

    void delete_review(int rid)
    {
        if (rid == review_id) {
            cout << "Review deleted for review ID: " << review_id << endl;
        } 
        else {
            throw Exception(1009,"can't delete your review");
        }
    }

    void get_review_details(int rid) {
        if (rid == review_id) {
            cout << "Review ID: " << review_id << endl;
            cout << "Product: " <<p->name << endl;
            cout << "Buyer ID: " << buyer_id << endl;
            cout << "Rating: " << rating << endl;
            cout << "Comment: " << comment << endl;
        } else {
            throw(1010,"we can't retrive your review details");
        }
    }
};

int main() {
    try {
        bool running = true;
        int choice;
        seller s("Alice","alice@example.com","123","Maple",1,"AliceStore",4.5);
        Buyer b("Bob","bob@example.com","456","Oak",1);

        do {
            cout << "\n==== MENU ====\n";
            cout << "1. Seller - Add Product\n";
            cout << "2. Seller - Delete Product\n";
            cout << "3. Seller - List Products\n";
            cout << "4. Buyer - Add to Wishlist\n";
            cout << "5. Buyer - Add to Cart\n";
            cout << "6. Buyer - View Wishlist\n";
            cout << "7. Buyer - View Cart\n";
            cout << "8. Buyer - Place Order\n";
            cout << "9. Buyer - View Order Status\n";
            cout << "10. Buyer - Invoice\n";
            cout << "11. Payment - Online\n";
            cout << "12. Payment - Offline\n";
            cout << "13. Review\n";
            cout << "14. Exit\n";
            cout << "Choice: ";
            cin >> choice;

            switch(choice) {
                case 1: {
                    int id,qty; string n; double pr;
                    cout << "Enter id,name,price,qty: ";
                    cin >> id; cin.ignore();
                    getline(cin,n); cin >> pr >> qty;
                    product p(id,n,pr,qty);
                    s.addProduct(p);
                    break;
                }
                case 2: {
                    int id;
                    cout << "Enter product id: ";
                    cin >> id;
                    s.deleteProduct(id);
                    break;
                }
                case 3: s.list_product(); break;
                case 4: {
                    int id,qty; string n; double pr;
                    cout << "Enter id,name,price,qty: ";
                    cin >> id; cin.ignore();
                    getline(cin,n); cin >> pr >> qty;
                    product p(id,n,pr,qty);
                    b.list_Wishlist(p);
                    break;
                }
                case 5: {
                    int id,qty; string n; double pr;
                    cout << "Enter id,name,price,qty: ";
                    cin >> id; cin.ignore();
                    getline(cin,n); cin >> pr >> qty;
                    product p(id,n,pr,qty);
                    b.add_to_cart(p);
                    break;
                }
                case 6: b.w.display(); break;
                case 7: b.c.displaydetails(); break;
                case 8: b.place_order(); break;
                case 9: {
                    int oid;
                    cout << "Enter order id: ";
                    cin >> oid;
                    b.view_order_status(oid);
                    break;
                }
                case 10: b.invoice(); break;
                case 11: {
                    int oid; string m,s,t;
                    cout << "Enter order id: "; cin >> oid;
                    cout << "Enter method,status,type: ";
                    cin.ignore(); getline(cin,m); getline(cin,s); getline(cin,t);
                    Order o(oid,"Bob"); // demo order
                    OnlinePayment op(oid,&o,m,s,t);
                    op.get_payment_details(oid);
                    break;
                }
                case 12: {
                    int oid; string m,s;
                    cout << "Enter order id: "; cin >> oid;
                    cout << "Enter method,status: ";
                    cin.ignore(); getline(cin,m); getline(cin,s);
                    Order o(oid,"Bob"); // demo order
                    OfflinePayment off(oid,&o,m,s);
                    off.get_payment_details(oid);
                    break;
                }
                case 13: {
                    int rid,bid,rt,pid,qty; string cm,n; double pr;
                    cout << "Enter rid,bid,pid: "; cin >> rid >> bid >> pid;
                    cout << "Name: "; cin.ignore(); getline(cin,n);
                    cout << "Price,qty,rating: "; cin >> pr >> qty >> rt;
                    cout << "Comment: "; cin.ignore(); getline(cin,cm);
                    product p(pid,n,pr,qty);
                    Review r(rid,&p,bid,rt,cm);
                    r.submit_review();
                    r.get_review_details(rid);
                    r.update_review(rid);
                    r.delete_review(rid);
                    break;
                }
                case 14: running = false; break;
                default: cout << "Invalid choice!\n";
            }

        } while(running);

    } catch(Exception &e) {
        e.show();
    }
}
