using GameDev;
using GameDev.Utilities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Content;

namespace GameDev.Exercises
{
    class BasicLogicExercise : Module
    {
        //Apollo Launch Status Checklist
        private bool _booster, _retro, _fido, _guidance, _surgeon, _eecom, _gnc,
            _telmu, _control, _procedures, _inco, _fao, _network, _recovery, _capcom;

        private bool _startIgnitionSequence;

        private TimeSpan _countdown;

        private KeyboardState _oldKeyboardState;

        private SpriteBatch _spriteBatch;
        private SpriteFont _font;

        private SpriteManager _spriteManager = new SpriteManager();
        private float _textureRatio = 17f;

        private Sprite[] _buttonSprites = new Sprite[15];
        private Sprite _controlBoardSprite = new Sprite(0);
        private Sprite _rocketSprite = new Sprite(1);
        private Sprite _towerSprite = new Sprite(2);
        private Sprite _countdownTimerSprite = new Sprite(3);

        public override void Create()
        {
            _booster = _retro = _fido = _guidance = _surgeon = _eecom = _gnc =
                _telmu = _control = _procedures = _inco = _fao = _network = _recovery = _capcom = false;

            _startIgnitionSequence = false;

            _countdown = new TimeSpan(0, 0, 10);
        }

        public override void LoadContent()
        {
            _graphicsDevice.BlendState = BlendState.AlphaBlend;

            _spriteBatch = new SpriteBatch(_graphicsDevice);

            _font = _contentManager.Load<SpriteFont>("Fonts\\QuartzMS");

            for (int i = 0; i < 15; ++i)
            {
                _buttonSprites[i] = new Sprite(1);
                _spriteManager.AddSprite(_buttonSprites[i]);
                SpriteTexture _spriteTexture = new SpriteTexture("Graphics\\Button");
                _spriteTexture.LoadContent(_contentManager);

                _buttonSprites[i].SetSpriteTexture(_spriteTexture);
                _buttonSprites[i].SetSize(_spriteTexture.ImageHeight / _textureRatio, _spriteTexture.ImageHeight / _textureRatio);
                _buttonSprites[i].SetVisible(false);
            }

            SpriteTexture controlBoardTexture = new SpriteTexture("Graphics\\Nasa_ControlBoard");
            controlBoardTexture.LoadContent(_contentManager);
            _controlBoardSprite.SetSpriteTexture(controlBoardTexture);
            _spriteManager.AddSprite(_controlBoardSprite);
            _controlBoardSprite.SetSize(controlBoardTexture.ImageWidth / _textureRatio, controlBoardTexture.ImageHeight / _textureRatio);

            SpriteTexture rocketTexture = new SpriteTexture("Graphics\\Rocket_launch");
            rocketTexture.LoadContent(_contentManager);
            _rocketSprite.SetSpriteTexture(rocketTexture);
            _spriteManager.AddSprite(_rocketSprite);
            _rocketSprite.SetSize(rocketTexture.ImageWidth / _textureRatio, rocketTexture.ImageHeight / _textureRatio);
            _rocketSprite.SetPosition(27f, -3f);

            SpriteTexture towerTexture = new SpriteTexture("Graphics\\Lift");
            towerTexture.LoadContent(_contentManager);
            _towerSprite.SetSpriteTexture(towerTexture);
            _spriteManager.AddSprite(_towerSprite);
            _towerSprite.SetSize(towerTexture.ImageWidth / _textureRatio, towerTexture.ImageHeight / _textureRatio);
            _towerSprite.SetPosition(27f, 1.2f);

            SpriteTexture countdownTimerTexture = new SpriteTexture("Graphics\\Countdown_Timer");
            countdownTimerTexture.LoadContent(_contentManager);
            _countdownTimerSprite.SetSpriteTexture(countdownTimerTexture);
            _spriteManager.AddSprite(_countdownTimerSprite);
            _countdownTimerSprite.SetSize(countdownTimerTexture.ImageWidth / _textureRatio, countdownTimerTexture.ImageHeight / _textureRatio);
            _countdownTimerSprite.SetPosition(26.2f, -17.8f);

            //top row
            _buttonSprites[0].SetPosition(-28.6f, 11.3f);
            _buttonSprites[1].SetPosition(-20.12f, 11.3f);
            _buttonSprites[2].SetPosition(-11.4f, 11.3f);
            _buttonSprites[3].SetPosition(-2.68f, 11.32f);
            _buttonSprites[4].SetPosition(6f, 11.32f);
            //middle row
            _buttonSprites[5].SetPosition(-28.6f, 2.18f);
            _buttonSprites[6].SetPosition(-20.12f, 2.18f);
            _buttonSprites[7].SetPosition(-11.4f, 2.18f);
            _buttonSprites[8].SetPosition(-2.68f, 2.16f);
            _buttonSprites[9].SetPosition(6f, 2.16f);
            //bottom row
            _buttonSprites[10].SetPosition(-28.6f, -6.52f);
            _buttonSprites[11].SetPosition(-20.12f, -6.52f);
            _buttonSprites[12].SetPosition(-11.4f, -6.52f);
            _buttonSprites[13].SetPosition(-2.68f, -6.52f);
            _buttonSprites[14].SetPosition(6f, -6.52f);
        }

        public override void UpdateInput(KeyboardState keyboardState, MouseState mouseState)
        {
            //*********** Begin Focus Area 1 ***********//
			// outer
            if (keyboardState.IsKeyDown(Keys.Q) && _oldKeyboardState.IsKeyUp(Keys.Q))
            {
                // inner
                    if (_booster)
                    {
                        _booster = false;
                    }
                    else
                    {
                        _booster = true;
                    }

                    _buttonSprites[0].SetVisible(_booster);
                
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.W) && _oldKeyboardState.IsKeyUp(Keys.W))
            {
				// middle
                
					// inner
                    if (_retro)
                    {
                        _retro = false;
                    }
                    else
                    {
                        _retro = true;
                    }

                    _buttonSprites[1].SetVisible(_retro);
                
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.E)&&_oldKeyboardState.IsKeyUp(Keys.E))
            {
				// middle
                
                
					// inner
                    if (_fido)
                    {
                        _fido = false;
                    }
                    else
                    {
                        _fido = true;
                    }

                    _buttonSprites[2].SetVisible(_fido);
                
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.R)&&_oldKeyboardState.IsKeyUp(Keys.R))
            {
				// middle
                
                
					// inner
                    if (_guidance)
                    {
                        _guidance = false;
                    }
                    else
                    {
                        _guidance = true;
                    }

                    _buttonSprites[3].SetVisible(_guidance);
                
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.T))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.T))
                {
					// inner 
                    if (_surgeon == true)
                    {
                        _surgeon = false;
                    }
                    else
                    {
                        _surgeon = true;
                    }

                    _buttonSprites[4].SetVisible(_surgeon);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.A))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.A))
                {
					// inner
                    if (_eecom == true)
                    {
                        _eecom = false;
                    }
                    else
                    {
                        _eecom = true;
                    }

                    _buttonSprites[5].SetVisible(_eecom);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.S))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.S))
                {
					// inner
                    if (_gnc == true)
                    {
                        _gnc = false;
                    }
                    else
                    {
                        _gnc = true;
                    }

                    _buttonSprites[6].SetVisible(_gnc);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.D))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.D))
                {
					// inner
                    if (_telmu == true)
                    {
                        _telmu = false;
                    }
                    else
                    {
                        _telmu = true;
                    }

                    _buttonSprites[7].SetVisible(_telmu);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.F))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.F))
                {
					// inner
                    if (_control == true)
                    {
                        _control = false;
                    }
                    else
                    {
                        _control = true;
                    }

                    _buttonSprites[8].SetVisible(_control);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.G))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.G))
                {
					// inner
                    if (_procedures == true)
                    {
                        _procedures = false;
                    }
                    else
                    {
                        _procedures = true;
                    }

                    _buttonSprites[9].SetVisible(_procedures);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.Z))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.Z))
                {
					// inner
                    if (_inco == true)
                    {
                        _inco = false;
                    }
                    else
                    {
                        _inco = true;
                    }

                    _buttonSprites[10].SetVisible(_inco);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.X))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.X))
                {
					// inner
                    if (_fao == true)
                    {
                        _fao = false;
                    }
                    else
                    {
                        _fao = true;
                    }

                    _buttonSprites[11].SetVisible(_fao);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.C))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.C))
                {
					// inner
                    if (_network == true)
                    {
                        _network = false;
                    }
                    else
                    {
                        _network = true;
                    }

                    _buttonSprites[12].SetVisible(_network);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.V))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.V))
                {
					// inner
                    if (_recovery == true)
                    {
                        _recovery = false;
                    }
                    else
                    {
                        _recovery = true;
                    }

                    _buttonSprites[13].SetVisible(_recovery);
                }
            }

			// outer
            if (keyboardState.IsKeyDown(Keys.B))
            {
				// middle
                if (_oldKeyboardState.IsKeyUp(Keys.B))
                {
					// inner
                    if (_capcom == true)
                    {
                        _capcom = false;                       
                    }
                    else
                    {
                        _capcom = true;
                    }

                    _buttonSprites[14].SetVisible(_capcom);
                }
            }
            //*********** End Focus Area 1 ***********//


            //*********** Begin Focus Area 2 ***********//
            // outer
			if (keyboardState.IsKeyDown(Keys.Space) && _oldKeyboardState.IsKeyUp(Keys.Space))
            {   
				// nested
                if (_booster == true)
                {
					// nested
                    if (_retro == true)
                    {
						// nested
                        if (_fido == true)
                        {
							// nested
                            if (_guidance == true)
                            {
								// nested
                                if (_surgeon == true)
                                {
									// nested
                                    if (_eecom == true)
                                    {
										// nested
                                        if (_gnc == true)
                                        {
											// nested
                                            if (_telmu == true)
                                            {
												// nested
                                                if (_control == true)
                                                {
													// nested
                                                    if (_procedures == true)
                                                    {
														// nested
                                                        if (_inco == true)
                                                        {
															// nested
                                                            if (_fao == true)
                                                            {
																// nested
                                                                if (_network == true)
                                                                {
																	// nested
                                                                    if (_recovery == true)
                                                                    {
																		// nested
                                                                        if (_capcom == true)
                                                                        {
                                                                            _startIgnitionSequence = true;
                                                                        }
                                                                        else
                                                                        {
                                                                            _startIgnitionSequence = false;
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        _startIgnitionSequence = false;
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    _startIgnitionSequence = false;
                                                                }
                                                            }
                                                            else
                                                            {
                                                                _startIgnitionSequence = false;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            _startIgnitionSequence = false;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        _startIgnitionSequence = false;
                                                    }
                                                }
                                                else
                                                {
                                                    _startIgnitionSequence = false;
                                                }
                                            }
                                            else
                                            {
                                                _startIgnitionSequence = false;
                                            }
                                        }
                                        else
                                        {
                                            _startIgnitionSequence = false;
                                        }
                                    }
                                    else
                                    {
                                        _startIgnitionSequence = false;
                                    }
                                }
                                else
                                {
                                    _startIgnitionSequence = false;
                                }
                            }
                            else
                            {
                                _startIgnitionSequence = false;
                            }
                        }
                        else
                        {
                            _startIgnitionSequence = false;
                        }
                    }
                    else
                    {
                        _startIgnitionSequence = false;
                    }
                }
                else
                {
                    _startIgnitionSequence = false;
                }
            }
            //*********** End Focus Area 2 ***********//


            _oldKeyboardState = keyboardState;
        }

        public override void Update(GameTime time)
        {
            // Extract the amount of time that has passed since the last update
            TimeSpan deltaTime = time.ElapsedGameTime;
            float deltaSeconds = (float)deltaTime.TotalSeconds;

            //*********** Begin Focus Area 3 ***********//
			// outer
            if (_startIgnitionSequence == true)
            {
                // inner
                if (_countdown.TotalSeconds > 0)
                {                    
                    _countdown = _countdown.Subtract(deltaTime);
                }
            }

            if (_countdown.TotalSeconds < 0)
            {
                //calculate the rocket's new position and set it
                _rocketSprite.SetPosition(_rocketSprite.Position.X, _rocketSprite.Position.Y + deltaSeconds + 0.1f);
            }

            //*********** End Focus Area 3 ***********//

        }

        public override void Render()
        {
            //render sprites
            _spriteManager.RenderSprites(_graphicsDevice, DefaultCamera);

            _spriteBatch.Begin();
            _spriteBatch.DrawString(_font, _countdown.Seconds.ToString(), new Vector2(1050, 605), Color.Black);
            _spriteBatch.End();
        }
    }
}
