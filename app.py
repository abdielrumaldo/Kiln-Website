from flask import Flask, render_template, flash, redirect, url_for
from forms import RegistrationForm, LoginForm
app = Flask(__name__)

app.config['SECRET_KEY'] = ''

controller_info = [
    {
        'name':'',
        'profile':'1',
        'segment':'7',
        'temp':'4',
        'ramp':'100',
        'soak':'200ms',
        'time':'14:32'
    }
]


@app.route('/main')
def main():
    return render_template('main.html', controller_info=controller_info, title='main')


@app.route('/menu')
def menu():
    return 'menu Page goes here'


@app.route('/')
@app.route('/locked')
def locked():
    return render_template('locked.html', controller_info=controller_info)


@app.route('/login', methods=['GET', 'POST'])
def login():
    form = LoginForm()
    if form.email.data == "admin@swau.edu" and form.password.data == 'password':
        flash(f'Logged in as Admin.', 'success')
        return redirect(url_for('main'))
    else:
        flash('Login unsucessful. Please check username and password', 'danger')
    return render_template('login.html', title='Login', form=form)


@app.route('/register', methods=['GET', 'POST'])
def register():
    form = RegistrationForm()
    if form.validate_on_submit():
        flash(f'Account created for {form.username.data}. You may now log in!', 'success')
        return redirect(url_for('login'))
    return render_template('register.html', title='Register', form=form)


if __name__ == '__main__':
    app.run(debug=True)
