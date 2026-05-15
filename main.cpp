#include<bits/stdc++.h>

using namespace std;

void generate_mcq(string question, vector<pair<string, bool>> options) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(options.begin(), options.end(), default_random_engine(seed));

    cout << "[Câu hỏi MCQ] " << question << "\n";
    char correct_label = 'A';
    for (int i = 0; i < 4; i++) {
        cout << char('A' + i) << ". " << options[i].first << "\n";
        if (options[i].second == true) {
            correct_label = char('A' + i);
        }
    }
    cout << "Đáp án đúng: " << correct_label << "\n\n";
}

// ==========================================
// TYPE 1: ARITHMETIC CODING (Encode & Decode)
// ==========================================
void solve_arithmetic(int mode) {
    string s; cin >> s;
    map<char, int> freq;
    for (char c : s) freq[c]++;
    
    map<char, pair<long double, long double>> prob_range;
    long double current_low = 0.0;
    
    if (mode == 1) cout << "--- LỜI GIẢI: MÃ HÓA & GIẢI MÃ SỐ HỌC ---\n[1] Bảng phân bổ xác suất:\n";
    for (auto const& [c, count] : freq) {
        long double p = (long double)count / s.length();
        prob_range[c] = {current_low, current_low + p};
        if (mode == 1) cout << "- Ký tự '" << c << "': [" << current_low << ", " << current_low + p << ")\n";
        current_low += p;
    }
    
    long double low = 0.0, high = 1.0;
    if (mode == 1) cout << "\n[2] Quá trình mã hóa chuỗi '" << s << "':\n";
    for (char c : s) {
        long double range = high - low;
        high = low + range * prob_range[c].second;
        low = low + range * prob_range[c].first;
        if (mode == 1) cout << "Đọc '" << c << "' -> Khoảng: [" << fixed << setprecision(6) << low << ", " << high << ")\n";
    }
    
    long double encoded_val = (low + high) / 2.0;
    if (mode == 1) {
        cout << "=> Giá trị mã hóa được chọn: " << encoded_val << "\n\n";
        cout << "[3] Quá trình giải mã (từ " << encoded_val << ", độ dài " << s.length() << "):\n";
        long double decode_val = encoded_val;
        for (int i = 0; i < s.length(); i++) {
            for (auto const& [c, range] : prob_range) {
                if (decode_val >= range.first && decode_val < range.second) {
                    cout << "Giá trị " << decode_val << " nằm trong khoảng của '" << c << "' -> Giải mã: " << c << "\n";
                    decode_val = (decode_val - range.first) / (range.second - range.first);
                    break;
                }
            }
        }
        cout << "\n";
    } else if (mode == 0) {
        cout << fixed << setprecision(6) << encoded_val << "\n";
    } else if (mode == 2) {
        string q = "Đâu là giá trị mã hóa số học hợp lệ của chuỗi '" + s + "'?";
        vector<pair<string, bool>> opts;
        opts.push_back({to_string(encoded_val), true});
        opts.push_back({to_string(encoded_val + 0.125), false});
        opts.push_back({to_string(low - 0.05), false}); 
        opts.push_back({to_string(high + 0.03), false}); 
        generate_mcq(q, opts);
    }
}

// ==========================================
// TYPE 2: LZW CODING (Encode & Decode)
// ==========================================
void solve_lzw(int mode) {
    string s; cin >> s;
    unordered_map<string, int> dict;
    vector<string> reverse_dict(4096);
    for (int i = 0; i < 256; i++) {
        dict[string(1, char(i))] = i;
        reverse_dict[i] = string(1, char(i));
    }
    
    if (mode == 1) cout << "--- LỜI GIẢI: MÃ HÓA & GIẢI MÃ LZW ---\n[1] Quá trình mã hóa chuỗi '" << s << "':\n";
    string p = ""; p += s[0];
    string c = ""; int code = 256;
    vector<int> output_code;
    
    for (int i = 0; i < s.length(); i++) {
        if (i != s.length() - 1) c += s[i + 1];
        if (dict.find(p + c) != dict.end()) {
            p = p + c;
        } else {
            if (mode == 1) cout << "Output: " << dict[p] << " | Thêm từ điển: " << p + c << " (Mã: " << code << ")\n";
            output_code.push_back(dict[p]);
            dict[p + c] = code;
            reverse_dict[code] = p + c;
            code++; p = c;
        }
        c = "";
    }
    output_code.push_back(dict[p]);
    if (mode == 1) {
        cout << "Output cuối: " << dict[p] << "\n=> Dãy mã hóa: ";
        for (int x : output_code) cout << x << " ";
        
        cout << "\n\n[2] Quá trình giải mã:\nChuỗi mã đầu vào: ";
        for (int x : output_code) cout << x << " "; cout << "\n";
        
        int old_code = output_code[0];
        string decoded_str = reverse_dict[old_code];
        cout << "Đọc " << old_code << " -> Xuất: " << decoded_str << "\n";
        int dec_code = 256; string temp_c = ""; temp_c += decoded_str[0];
        
        for (int i = 1; i < output_code.size(); i++) {
            int new_code = output_code[i];
            string entry;
            if (reverse_dict[new_code] != "") {
                entry = reverse_dict[new_code];
            } else {
                entry = reverse_dict[old_code] + temp_c;
            }
            cout << "Đọc " << new_code << " -> Xuất: " << entry << " | Thêm từ điển: " << reverse_dict[old_code] + entry[0] << " (Mã: " << dec_code++ << ")\n";
            decoded_str += entry;
            temp_c = ""; temp_c += entry[0];
            old_code = new_code;
        }
        cout << "=> Chuỗi giải mã thành công: " << decoded_str << "\n\n";
    } else if (mode == 0) {
        for (int x : output_code) cout << x << " "; cout << "\n";
    } else if (mode == 2) {
        string q = "Số lượng từ mã sinh ra sau khi nén LZW chuỗi '" + s + "' là bao nhiêu?";
        int ans = output_code.size();
        vector<pair<string, bool>> opts;
        opts.push_back({to_string(ans), true});
        opts.push_back({to_string(ans + 1), false});
        opts.push_back({to_string(ans - 1 > 0 ? ans - 1 : ans + 2), false});
        opts.push_back({to_string(ans + 3), false});
        generate_mcq(q, opts);
    }
}

// ==========================================
// TYPE 3: HAMMING DISTANCE & ERROR CAPABILITY
// ==========================================
void solve_hamming(int mode) {
    int n; cin >> n;
    vector<string> codes(n);
    for (int i = 0; i < n; i++) cin >> codes[i];
    
    int d_min = 1e9; string pair1, pair2;
    if (mode == 1) cout << "--- LỜI GIẢI: KHẢ NĂNG PHÁT HIỆN & SỬA LỖI ---\n";
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = 0;
            for (int k = 0; k < codes[i].length(); k++) {
                if (codes[i][k] != codes[j][k]) dist++;
            }
            if (mode == 1) cout << "Khoảng cách d(" << codes[i] << ", " << codes[j] << ") = " << dist << "\n";
            if (dist < d_min) { d_min = dist; pair1 = codes[i]; pair2 = codes[j]; }
        }
    }
    
    int detect = d_min - 1;
    int correct = (d_min - 1) / 2;
    
    if (mode == 0) {
        cout << d_min << " " << detect << " " << correct << "\n";
    } else if (mode == 1) {
        cout << "=> d_min = " << d_min << " (Giữa " << pair1 << " và " << pair2 << ")\n";
        cout << "=> Khả năng phát hiện lỗi (e) = d_min - 1 = " << detect << " bit.\n";
        cout << "=> Khả năng sửa lỗi (t) = floor((d_min - 1) / 2) = " << correct << " bit.\n\n";
    } else if (mode == 2) {
        string q = "Khả năng sửa lỗi tối đa (t) của bộ mã đầu vào là bao nhiêu bit?";
        vector<pair<string, bool>> opts;
        opts.push_back({to_string(correct) + " bit", true});
        opts.push_back({to_string(correct + 1) + " bit", false});
        opts.push_back({to_string(detect) + " bit", false});
        opts.push_back({to_string(d_min) + " bit", false});
        generate_mcq(q, opts);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            int type, mode; cin >> type >> mode;
            if (type == 1) solve_arithmetic(mode);
            else if (type == 2) solve_lzw(mode);
            else if (type == 3) solve_hamming(mode);
        }
    }
    return 0;
}