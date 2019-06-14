/* serialize/deserialize a hierarchical file system, or more generally:
* serialize/deserialize a dynamically sized tree (variable N-ary tree)
*/

/* file can either hold data or other files (be a directory) */
struct file{
    file_attributes attr;
    string name;
    vector<file> directory;
};

/*output vector is basically a post order travsersal, but with a marker
* (in this case a file called ")") put each time you move up the tree in
* the travseral (like after you visit a leaf node)
*/
void serialize(file *root, vector<file> *out){
    file mark;
    mark.name = ")";
    for(int i=0; i<root->directory.size(); i++){
        out->push_back(root->directory[i]);
        if(root->directory[i].directory.empty())
            out->push_back(mark);
        else
            serialize(&root->directory[i], out);
    }
    out->push_back(mark);
    return;
}
/* given a vector that holds the result of serialization, recontruct
* the tree starting at the given root node
*/
int deSerialize(file *root, vector<file> *in, bool recursed){
    if(in->size() == 0 || in->at(0).name.compare(")")==0)
        return 0;
    
    while(in->size() > 0){
        if(in->at(0).name.compare(")")!=0){
            recursed = false;
            file top = in->at(0);
            root->directory.push_back(top);
            in->erase(in->begin());
            deSerialize(&root->directory[ root->directory.size()-1  ],
                       in, recursed);
        }
        else{
            if(recursed)
                return 0;
            in->erase(in->begin());
            recursed = true;
        }
    }
    return 0;
} 


////////////////////////////////////
